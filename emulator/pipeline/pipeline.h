#pragma once

#include "../memory/memory.h"
//#include "instructions.hpp"
#include <fstream>
#include <map>

using std::string;
using std::ifstream;

//TODO:: remove this file but before replace functional to emulator or another file

class Pipeline {
public:
    Pipeline(RAM &, ifstream);

    int getCurrentState(); // return number of ticks taken
    int makeStep(); // call this from Emulator to perform one operation, returns number of instructions
private:



    string instructionLine; // set in fetch
    string tokens[3]; // set in decode
    commandDecomposed command; // set in LoadOpCode
    OPERAND_TYPE opTypes[3]; // set in LoadOpCode, types of operands we work with
    uint8_t byteTempResult;
    uint16_t wordTempResult;

    Pipeline(Pipeline const &) = delete;

    Pipeline &operator=(Pipeline const &) = delete;

    uint16_t *generalPurpReg[5]; // should be mapped to Reg memory in constructor

};

