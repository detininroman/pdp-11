#pragma once

#include "error.hpp"
#include "instructions/instructions.hpp"
#include "memory/memory.hpp"
#include "command_executer.hpp"
#include "pipeline.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

struct StateVariables {
    uint16_t fetched_bytes;
    struct Instruction *current_instr;
    uint8_t offset;
    uint8_t mode_source, source, mode_dest, dest;
    uint8_t reg, mode;
};

class Emulator {
public:
    Emulator() = default;

    static Emulator &instance();

    Error initROM(std::string fileName);

    Error step();

    size_t getVideoMemory(uint8_t *buff, size_t size) const;

    size_t getROM(uint8_t *buff, size_t size) const;

    std::string getAssembly() const;

    uint16_t getRegister(RegisterEnum reg);

    bool getProcessorStatusWord(ProcessorStatusWordEnum psw);

    int getTicks();

private:
    ~Emulator();

    Emulator(Emulator const &emulator) = delete;

    Emulator &operator=(Emulator const &emulator) = delete;

    StateVariables emulator_state;

    Memory memory;

    Pipeline pipeline;

    std::stringstream assembly;

    void _fetch();

    void _decode();

    void _loadOperands();

    void _execute();

    //Action fetch, decode, loadOperands, execute;

    uint16_t *pullOutAddress(uint8_t reg_num, uint8_t mode_num);

    std::string formatOperand(uint8_t reg_num, uint8_t mode_num);
};
