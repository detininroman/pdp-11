#include "emulator.hpp"
#include "memory/memory.hpp"

enum class AddressingMode {
    DIRECT = 0,
    REG_DEFERRED = 1,
    AUTO_INC = 2,
    AUTO_INC_DEFERRED = 3,
    AUTO_DEC = 4,
    AUTO_DEC_DEFERRED = 5,
    INDEX = 6,
    INDEX_DEFERRED = 7,
};

Emulator::~Emulator() {
}

Emulator &Emulator::instance() {
    static Emulator e;
    return e;
}

int Emulator::getTicks() {
    return 1488;
}

Error Emulator::step() {
    if (memory.registers.pc == RAM_SIZE + VIDEO_SIZE + ROM_SIZE) {
        return Error::FINISHED;
    }
    emulator_state = StateVariables();
    fetch();
    decode();
    loadOperands();
    execute();
    return Error::OK;
}

size_t Emulator::getVideoMemory(uint8_t *buff, size_t size) const {
    return memory.getVideoMemory(buff, size);
}

size_t Emulator::getROM(uint8_t *buff, size_t size) const {
    return memory.getROM(buff, size);
}

std::vector<std::string> Emulator::getByteCode() const {
    return byteCode;
}

std::string Emulator::getAssembly() const {
    return assembly.str();
}

std::vector<std::string> Emulator::getAssemblyCommands() const {
    std::string cmd;
    std::stringstream ss(getAssembly());
    std::vector<std::string> commands;

    while (std::getline(ss, cmd, '\n')) {
        commands.push_back(cmd);
    }
    return commands;
}

std::vector<std::string> Emulator::getAssemblyCommands(int n) const {
    std::vector<std::string> vec = getAssemblyCommands();
    std::vector<std::string> res;
    int size = vec.size();

    for (int i = size - n; i < size; i++) {
        res.push_back(vec[i]);
    }
    return res;
}

Error Emulator::initROM(std::string fileName) {
    std::ifstream codeStream(fileName, std::ios::binary | std::ios::ate);
    if (!codeStream.is_open()) {
        throw std::runtime_error("Error opening ROM file!");
    }
    // initing ROM
    std::ifstream::pos_type end_pos = codeStream.tellg();
    int len = codeStream.tellg();
    codeStream.seekg(0, std::ios::beg);
    std::unique_ptr<uint8_t> mem(new uint8_t[len]);
    codeStream.read(reinterpret_cast<char *>(mem.get()), end_pos);

    if (memory.init(mem.get(), len) != Error::OK) {
        throw std::runtime_error("Error initializing memory!");
    }

    memory.registers.pc = RAM_SIZE + VIDEO_SIZE;
    codeStream.close();
    return Error::OK;
}

uint16_t Emulator::getRegister(RegisterEnum reg) {
    return *(&memory.registers.r0 + reg);
}

bool Emulator::getProcessorStatusWord(ProcessorStatusWordEnum psw) {
    return *(&memory.registers.psw.N + psw);
}

void Emulator::fetch() {
    memset(reinterpret_cast<char *>(&emulator_state.fetched_bytes), 0x0, 2);
    uint16_t *memory_pointer;
    memory.getWordAddress(memory.registers.pc, &memory_pointer);
    // little to big endian
    //emulator_state.fetched_bytes = ((*memory_pointer & 0x00FF) << 8) | ((*memory_pointer & 0xFF00) >> 8);
    emulator_state.fetched_bytes = *memory_pointer;
    memory.registers.pc += 2;

    std::stringstream cmd;
    cmd << "0x" << std::hex << emulator_state.fetched_bytes;
    byteCode.push_back(cmd.str());
}

void Emulator::decode() {
    emulator_state.current_instr = nullptr;

    for (auto &instr : kInstructionTable) {
        auto mask = instr.mask;
        auto opcode = instr.opcode;

        if ((mask & emulator_state.fetched_bytes) == opcode) {
            emulator_state.current_instr = const_cast<Instruction *>(&instr);
            break;
        }
    }

    if (!emulator_state.current_instr) {
        throw std::runtime_error("Found command with invalid opcode!");
    }
}

void Emulator::loadOperands() {
    switch (emulator_state.current_instr->type) {
        case InstructionType::CONDITIONAL_BRANCH : {
            emulator_state.offset = (emulator_state.fetched_bytes & 0b0000000011111111);
            break;
        }
        case InstructionType::DOUBLE_OPERAND : {
            // 11 to 9 bytes
            emulator_state.mode_source = (emulator_state.fetched_bytes & 0b0000111000000000) >> 9;
            // 8 to 6 bytes
            emulator_state.source = (emulator_state.fetched_bytes & 0b0000000111000000) >> 6;
            // 5 to 3 bytes
            emulator_state.mode_dest = (emulator_state.fetched_bytes & 0b0000000000111000) >> 3;
            // 2 to 0 bytes
            emulator_state.dest = (emulator_state.fetched_bytes & 0b0000000000000111);

            //emulator_state.source_reg = memory.reg_table[emulator_state.source];
            break;
        }
        case InstructionType::DOUBLE_OPERAND_REG : {
            emulator_state.mode_source = 0;
            // 8 to 6 bytes
            emulator_state.source = (emulator_state.fetched_bytes & 0b0000000111000000) >> 6;
            // 5 to 3 bytes
            emulator_state.mode_dest = (emulator_state.fetched_bytes & 0b0000000000111000) >> 3;
            // 2 to 0 bytes
            emulator_state.dest = (emulator_state.fetched_bytes & 0b0000000000000111);

            break;
        }
        case InstructionType::SINGLE_OPERAND : {
            // 5 to 3 bytes
            emulator_state.mode = (emulator_state.fetched_bytes & 0b0000000000111000) >> 3;
            // 2 to 0 bytes
            emulator_state.reg = (emulator_state.fetched_bytes & 0b0000000000000111);

            break;
        }
        case InstructionType::NO_OPERAND : {
            // for HALT
            break;
        }
        default:
            throw std::runtime_error("Invalid operation type");
    }
}

void Emulator::execute() {
    assembly << emulator_state.current_instr->name << ' ';

    switch (emulator_state.current_instr->type) {
        case InstructionType::CONDITIONAL_BRANCH : {
            break;
        }
        case InstructionType::DOUBLE_OPERAND :
        case InstructionType::DOUBLE_OPERAND_REG : {

            uint16_t *operand1 = pullOutAddress(emulator_state.source, emulator_state.mode_source);

            uint16_t *operand2 = pullOutAddress(emulator_state.dest, emulator_state.mode_dest);

            if (operand1 && operand2) {

                emulator_state.current_instr->callback(&memory.registers, operand1, operand2);
            }

            assembly << formatOperand(emulator_state.source, emulator_state.mode_source) << ' ' <<
                     formatOperand(emulator_state.dest, emulator_state.mode_dest) << '\n';

            break;
        }
        case InstructionType::SINGLE_OPERAND : {
            uint16_t *operand = pullOutAddress(emulator_state.reg, emulator_state.mode);

            if (operand) {
                emulator_state.current_instr->callback(&memory.registers, operand, nullptr);
            }

            assembly << formatOperand(emulator_state.reg, emulator_state.mode) << '\n';

            break;
        }
        case InstructionType::NO_OPERAND : {
            // for HALT
            emulator_state.current_instr->callback(&memory.registers, nullptr, nullptr);

            assembly << '\n';

            break;
        }
        default:
            throw std::runtime_error("Invalid operation type");
    }
}

uint16_t *Emulator::pullOutAddress(uint8_t reg_num, uint8_t mode_num) {
    AddressingMode addressing_mode = static_cast<AddressingMode> (mode_num);
    uint16_t *address = nullptr; // here we write contents of reg
    uint16_t *reg_pointer = memory.reg_table[reg_num];
    switch (addressing_mode) {
        case AddressingMode::DIRECT : {
            return reg_pointer; // address of reg
        }
        case AddressingMode::REG_DEFERRED : { // Contents of Reg is the address
            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) { // address stored in reg
                return address;
            } else {
                return nullptr; // Take care
            }
        }
        case AddressingMode::AUTO_INC : { // Contents of Reg is the address, then Reg incremented

            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) { // address stored in reg

                *reg_pointer += 2;
                return address;

            } else {

                return nullptr; // Take care
            }
        }
        case AddressingMode::AUTO_INC_DEFERRED : { // Content of Reg is addr of addr, then Reg Incremented
            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) { // address stored in reg
                uint16_t *address2 = nullptr;
                if (memory.getWordAddress(*address, &address2) == Error::OK) { // address of address stored in reg
                    *reg_pointer += 2;
                    return address2;
                } else { // smth wrong with second address
                    return nullptr; // Take care
                }
            } else {
                return nullptr; // Take care
            }
        }
        case AddressingMode::AUTO_DEC : { // Reg is decremented then contents is address
            if (*reg_pointer >= 2) { // important to check, not to overflow unsigned
                *reg_pointer -= 2;
            } else {
                return nullptr; // Take care
            }
            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) {
                return address;
            } else {
                *reg_pointer += 2; // restore reg in case of error
                return nullptr; // Take care
            }
        }
        case AddressingMode::AUTO_DEC_DEFERRED : { // Reg is decremented then contents is addr of addr
            if (*reg_pointer >= 2) { // important to check, not to overflow unsigned
                *reg_pointer -= 2;
            } else {
                return nullptr; // Take care
            }
            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) {
                uint16_t *address2 = nullptr;
                if (memory.getWordAddress(*address, &address2) == Error::OK) {
                    *reg_pointer += 2;
                    return address2;
                } else {
                    *reg_pointer += 2; // restore reg in case of error
                    return nullptr; // Take care
                }
            } else {
                *reg_pointer += 2; // restore reg in case of error
                return nullptr; // Take care
            }
        }
        case AddressingMode::INDEX : { // Contents of Reg + Following word is address
            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) { // obtaining contents of reg
                uint16_t *address2 = nullptr;
                if (memory.getWordAddress((*reg_pointer + 2), &address2) == Error::OK) { // following word
                    uint16_t *output_address = nullptr;
                    if (memory.getWordAddress((*address + *address2), &output_address) ==
                        Error::OK) { // by summ of addr
                        return output_address;
                    } else {
                        return nullptr; // Take care
                    }
                } else {
                    return nullptr; // Take care
                }
            }
            return nullptr; // Take care
        }
        case AddressingMode::INDEX_DEFERRED : { // Contents of Reg + Following word is addr of addr
            if (memory.getWordAddress(*reg_pointer, &address) == Error::OK) {  // obtaining contents of reg
                uint16_t *address2 = nullptr;
                if (memory.getWordAddress((*reg_pointer + 2), &address2) == Error::OK) { // following word
                    uint16_t *address3 = nullptr;
                    if (memory.getWordAddress((*address + *address2), &address3) == Error::OK) { // by summ of addr
                        uint16_t *output_address = nullptr;
                        if (memory.getWordAddress((*address + *address2), &output_address) ==
                            Error::OK) { // go to address
                            return output_address;
                        } else {
                            return nullptr; // Take care
                        }
                    } else {
                        return nullptr; // Take care
                    }
                } else {
                    return nullptr; // Take care
                }
            }
            return nullptr; // Take care
        }
        default : {
            break;
        }
    }
    return nullptr; // Take care
}

std::string Emulator::formatOperand(uint8_t reg_num, uint8_t mode_num) {
    AddressingMode addressing_mode = static_cast<AddressingMode>(mode_num);
    std::string reg_name = "r" + std::to_string(reg_num);
    std::string operand;
    switch (addressing_mode) {
        case AddressingMode::DIRECT :
            return reg_name;

        case AddressingMode::REG_DEFERRED :
            return "(" + reg_name + ")";

        case AddressingMode::AUTO_INC :
            return "(" + reg_name + ")+";

        case AddressingMode::AUTO_INC_DEFERRED :
            return "@(" + reg_name + ")+";

        case AddressingMode::AUTO_DEC :
            return "-(" + reg_name + ")";

        case AddressingMode::AUTO_DEC_DEFERRED :
            return "@-(" + reg_name + ")";

        case AddressingMode::INDEX :
            return "X(" + reg_name + ")";

        case AddressingMode::INDEX_DEFERRED :
            return "@X(" + reg_name + ")";

        default :
            break;

    }
    return "";
}