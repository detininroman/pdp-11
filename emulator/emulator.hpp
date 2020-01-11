#pragma once

#include "memory/memory.hpp"
#include "pipeline/instructions.hpp"

#include <fstream>
#include <map>
#include <string>

class Emulator {

public:
    static uint8_t getVideo();

    bool initROM(std::string fileName);

    void startAll();

    static void step();

    static Emulator& instance();

private:
    Emulator();
    ~Emulator();

    Emulator(Emulator const &emulator) = delete;
    Emulator &operator=(Emulator const &emulator) = delete;

    typedef enum {
        FETCH,
        DECODE,
        LOAD_OPERAND,
        EXCECUTE,
        STORE_RES
    } PIPELINE_STAGE;

    int ticks;
    // TODO:: move to another class, change according to real data
    const int defaultTicksAddCount = 50;

    PIPELINE_STAGE currentStage;

    RAM Ram;
    Video vRam;
    std::map<std::string, commandDecomposed> instructionTable;

    std::ifstream codeStream;

    void fetch();

    void decode();

    void loadOperand();

    void execute();

    void storeRes();

    void initTable();
};
