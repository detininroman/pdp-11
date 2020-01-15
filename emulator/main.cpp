#include "emulator.hpp"

int main() {
    Emulator::instance().initROM("../programs/white_screen");
    return 0;
}
