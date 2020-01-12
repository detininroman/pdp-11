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
        return false;
    }
    return true;
}

void Emulator::startAll() {

}

