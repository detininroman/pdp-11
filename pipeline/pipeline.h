#pragma once

#include "../memory/memory.h"
#include "instructions.hpp"
#include <fstream>
#include <map>

using std::string;
using std::ifstream;

enum PIPELINE_STAGE {
    FETCH,
    DECODE,
    LOAD_OPCODE,
    EXCECUTE,
    STORE_RES
};

class Pipeline {
public:
    Pipeline(RAM &, ifstream);

    int getCurrentState(); // return number of ticks taken
    int makeStep(); // call this from Emulator to perform one operation, returns number of instructions
private:
    void fetch();

    void decode();

    void loadOpcode();

    void execute();

    void storeRes();

    void initTable();


    PIPELINE_STAGE stage;

    ifstream codeFromFile;
    string instructionLine; // set in fetch
    string tokens[3]; // set in decode
    commandDecomposed command; // set in LoadOpCode
    OPERAND_TYPE opTypes[3]; // set in LoadOpCode, types of operands we work with
    uint8_t byteTempResult;
    uint16_t wordTempResult;

    Pipeline(Pipeline const &) = delete;

    Pipeline &operator=(Pipeline const &) = delete;

    uint16_t *generalPurpReg[5]; // should be mapped to Reg memory in constructor

    RAM Ram;
    Video vRam;
    std::map<std::string, commandDecomposed> instructionTable;
};

