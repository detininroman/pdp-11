#include "emulator.hpp"

Emulator::Emulator() : ticks(0) {
}

Emulator::~Emulator() {
    codeStream.close();
}

Emulator &Emulator::instance() {
    static Emulator e;
    return e;
}

bool Emulator::initROM(std::string fileName) {
    codeStream.open(fileName, std::fstream::in);
    if (!codeStream.is_open()) {
        throw std::runtime_error("Error opening ROM file!");
    }
    return true;
}

void Emulator::fetch() {
    memset(reinterpret_cast<char *>(&fetched_bytes), 0x0, 2);
    codeStream.read(reinterpret_cast<char *>(&fetched_bytes), 2);
}

void Emulator::decode() {
    current_instr = nullptr;
    for (auto& instr : instructionTable) {
        auto mask = instr.mask;
        auto opcode = instr.opcode;
        if ((mask && fetched_bytes) == opcode) {
            current_instr = const_cast<Instruction *>(&instr);
            break;
        }
    }
    if (!current_instr){
        throw std::runtime_error("Found command with invalid opcode!");
    }
}

void Emulator::startAll() {

}

