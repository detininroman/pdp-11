#include "emulator.hpp"

int main() {
    Emulator::instance().initROM("../programs/white_screen2");
    for(int i = 0; i < 10; i++){
        Emulator::instance().step();

    }
    return 0;
}