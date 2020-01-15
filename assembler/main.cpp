#include <iostream>
#include <fstream>

#include "assembler.hpp"

int main() {
    std::ifstream asmStream("../programs/white_screen.s");
    Assembler assembler;
    assembler.generateHumanReadable(asmStream, "white_screen_gen");
    return 0;
}
