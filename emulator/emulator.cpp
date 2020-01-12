#include "emulator.hpp"
#include "error.hpp"

Emulator::~Emulator() {
}

Emulator &Emulator::instance() {
    static Emulator e;
    return e;
}

bool Emulator::initROM(std::string fileName) {
    std::ifstream codeStream(fileName, std::ios::binary | std::ios::ate);
    if (!codeStream.is_open()) {
        throw std::runtime_error("Error opening ROM file!");
    }
    //initing ROM
    std::ifstream::pos_type end_pos = codeStream.tellg();
    int len = codeStream.tellg();
    codeStream.seekg(0, std::ios::beg);
    std::unique_ptr <uint8_t> mem(new uint8_t[len]);
    codeStream.read(reinterpret_cast<char *>(mem.get()), end_pos);
    if (memory.init(mem.get(), len) != ERROR_OK) {
        throw std::runtime_error("Error initializing memory!");
    }

    memory.registers.pc = RAM_SIZE + VIDEO_SIZE;
    codeStream.close();
    return true;
}

void Emulator::fetch() {
    memset(reinterpret_cast<char *>(&fetched_bytes), 0x0, 2);
    memory.getWordValue(memory.registers.pc, fetched_bytes);
    memory.registers.pc += 2;
}

void Emulator::decode() {
    current_instr = nullptr;
    for (auto &instr : instructionTable) {
        auto mask = instr.mask;
        auto opcode = instr.opcode;
        if ((mask && fetched_bytes) == opcode) {
            current_instr = const_cast<Instruction *>(&instr);
            break;
        }
    }
    if (!current_instr) {
        throw std::runtime_error("Found command with invalid opcode!");
    }

}

void Emulator::startAll() {

}

