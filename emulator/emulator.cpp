#include "emulator.hpp"
#include "memory/memory.hpp"

Emulator::~Emulator() {
}

Emulator &Emulator::instance() {
    static Emulator e;
    return e;
}

size_t Emulator::getVideoMemory(uint8_t *buff, size_t size) const {
    return memory.getVideoMemory(buff, size);
}

Error Emulator::initROM(std::string fileName) {
    std::ifstream codeStream(fileName, std::ios::binary | std::ios::ate);
    if (!codeStream.is_open()) {
        throw std::runtime_error("Error opening ROM file!");
    }
    //initing ROM
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
    return *(&memory.registers.r0+reg);
}

bool Emulator::getProcessorStatusWord(ProcessorStatusWordEnum psw) {
    return *(&memory.registers.psw.N+psw);
}

int Emulator::getTicks() {
    return 1488;
}

void Emulator::fetch() {
    memset(reinterpret_cast<char *>(&emulator_state.fetched_bytes), 0x0, 2);
    memory.getWordValue(memory.registers.pc, &emulator_state.fetched_bytes);
    memory.registers.pc += 2;
}

void Emulator::decode() {
    emulator_state.current_instr = nullptr;
    for (auto &instr : instructionTable) {
        auto mask = instr.mask;
        auto opcode = instr.opcode;
        if ((mask && emulator_state.fetched_bytes) == opcode) {
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
            emulator_state.mode_source = (emulator_state.fetched_bytes & 0b0000011100000000) >> 8;
            // 8 to 6 bytes
            emulator_state.source = (emulator_state.fetched_bytes & 0b0000000011110000) >> 5;
            // 5 to 3 bytes
            emulator_state.mode_dest = (emulator_state.fetched_bytes & 0b0000000000111000) >> 3;
            // 2 to 0 bytes
            emulator_state.dest = (emulator_state.fetched_bytes & 0b0000000000000111);

            // decoding registers
            emulator_state.source_reg = memory.reg_table[emulator_state.source];
            emulator_state.dest_reg = memory.reg_table[emulator_state.dest];
            break;
        }
        case InstructionType::DOUBLE_OPERAND_REG : {
            emulator_state.mode_source = 0;
            // 8 to 6 bytes
            emulator_state.source = (emulator_state.fetched_bytes & 0b0000000011110000) >> 5;
            // 5 to 3 bytes
            emulator_state.mode_dest = (emulator_state.fetched_bytes & 0b0000000000111000) >> 3;
            // 2 to 0 bytes
            emulator_state.dest = (emulator_state.fetched_bytes & 0b0000000000000111);

            // decoding registers
            emulator_state.source_reg = memory.reg_table[emulator_state.source];
            emulator_state.dest_reg = memory.reg_table[emulator_state.dest];

            break;
        }
        case InstructionType::SINGLE_OPERAND : {
            // 5 to 3 bytes
            emulator_state.mode = (emulator_state.fetched_bytes & 0b0000000000111000) >> 3;
            // 2 to 0 bytes
            emulator_state.reg = (emulator_state.fetched_bytes & 0b0000000000000111);

            // decoding registers
            emulator_state.dest_reg = memory.reg_table[emulator_state.reg];
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
    switch (emulator_state.current_instr->type) {
        case InstructionType::CONDITIONAL_BRANCH : {
            break;
        }
        case InstructionType::DOUBLE_OPERAND: {
            uint16_t *operand1 = pull_out_address(emulator_state.source, emulator_state.mode_source);
            uint16_t *operand2 = pull_out_address(emulator_state.dest, emulator_state.mode_dest);
            if(operand1 && operand2){
                emulator_state.current_instr->callback(&memory.registers, operand1, operand2); // TODO: check errorcodes
            }
            break;
        }
        case InstructionType::DOUBLE_OPERAND_REG : {
            uint16_t *operand1 = pull_out_address(emulator_state.source, emulator_state.mode_source);
            uint16_t *operand2 = pull_out_address(emulator_state.dest, emulator_state.mode_dest);
            if(operand1 && operand2) {
                emulator_state.current_instr->callback(&memory.registers, operand1, operand2);
            }
            break;
        }
        case InstructionType::SINGLE_OPERAND : {
            uint16_t *operand = pull_out_address(emulator_state.reg, emulator_state.mode);
            if(operand){
                emulator_state.current_instr->callback(&memory.registers, operand, nullptr);
            }
            break;
        }
        case InstructionType::NO_OPERAND : {
            // for HALT
            emulator_state.current_instr->callback(&memory.registers, nullptr, nullptr);
            break;
        }
        default:
            throw std::runtime_error("Invalid operation type");
    }

}

void Emulator::startAll() {

}

uint16_t *Emulator::pull_out_address(uint8_t reg_num, uint8_t mode_num) {
    uint16_t *address = nullptr; // here we write contents of reg
    uint16_t *reg_pointer = memory.reg_table[reg_num];
    switch (mode_num) {
        case 0 : { // Direct addressing of the register
            return reg_pointer; // address of reg
        }
        case 1 : { // Contents of Reg is the address
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) { // address stored in reg
                return address;
            } else {
                return nullptr; // Take care
            }
        }
        case 2 : { // Contents of Reg is the address, then Reg incremented
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) { // address stored in reg
                *reg_pointer += 2;
                return address;
            } else {
                return nullptr; // Take care
            }
        }
        case 3 : { // Content of Reg is addr of addr, then Reg Incremented
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) { // address stored in reg
                uint16_t *address2 = nullptr;
                if (memory.getWordValue(*address, address2) == Error::OK) { // address of address stored in reg
                    *reg_pointer += 2;
                    return address2;
                } else { // smth wrong with second address
                    return nullptr; // Take care
                }
            } else {
                return nullptr; // Take care
            }
        }
        case 4 : { // Reg is decremented then contents is address
            if (*reg_pointer >= 2) { // important to check, not to overflow unsigned
                *reg_pointer -= 2;
            } else {
                return nullptr; // Take care
            }
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) {
                return address;
            } else {
                *reg_pointer += 2; // restore reg in case of error
                return nullptr; // Take care
            }
        }
        case 5 : { // Reg is decremented then contents is addr of addr
            if (*reg_pointer >= 2) { // important to check, not to overflow unsigned
                *reg_pointer -= 2;
            } else {
                return nullptr; // Take care
            }
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) {
                uint16_t *address2 = nullptr;
                if (memory.getWordValue(*address, address2) == Error::OK) {
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
        case 6 : { // Contents of Reg + Following word is address
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) { // obtaining contents of reg
                uint16_t *address2 = nullptr;
                if (memory.getWordValue((*reg_pointer + 2), address2) == Error::OK) { // following word
                    uint16_t *output_address = nullptr;
                    if (memory.getWordValue((*address + *address2), output_address) == Error::OK) { // by summ of addr
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
        case 7 : { // Contents of Reg + Following word is addr of addr
            if (memory.getWordValue(*reg_pointer, address) == Error::OK) {  // obtaining contents of reg
                uint16_t *address2 = nullptr;
                if (memory.getWordValue((*reg_pointer + 2), address2) == Error::OK) { // following word
                    uint16_t *address3 = nullptr;
                    if (memory.getWordValue((*address + *address2), address3) == Error::OK) { // by summ of addr
                        uint16_t *output_address = nullptr;
                        if (memory.getWordValue((*address + *address2), output_address) == Error::OK) { // go to address
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
