#include <iostream>
#include <fstream>

#include "assembler.hpp"

int main(int argc, char *argv[]) {
    std::string asm_file = argc > 1 ? argv[1] : "../programs/white_screen.s";
    const char *bin_file = argc > 2 ? argv[2] : "white_screen";

    std::ifstream asmStream(asm_file);
    Assembler assembler;
    assembler.generateBinary(asmStream, bin_file);

    return 0;
}
