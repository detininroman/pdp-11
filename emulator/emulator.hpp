#pragma once

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "error.hpp"
#include "instructions/instructions.hpp"
#include "memory/memory.hpp"
#include "pipeline.hpp"


struct StateVariables {
    uint16_t fetched_bytes;
    struct Instruction *current_instr;
    uint8_t offset;
    uint8_t mode_source, source, mode_dest, dest;
    uint8_t reg, mode;
};

class Emulator {
public:
    static Emulator &instance();

    Error initROM(std::string fileName);

    Error step();

    size_t getVideoMemory(uint8_t *buff, size_t size) const;

    void cleanVideoMemory();

    size_t getROM(uint8_t *buff, size_t size) const;

    std::vector<std::string> getByteCode() const;

    std::vector<std::string> getByteCode(int n) const;

    void cleanByteCode();

    std::string getAssembly() const;

    std::vector<std::string> getAssemblyCommands() const;

    std::vector<std::string> getAssemblyCommands(int n) const;

    void cleanAssembly();

    uint16_t getRegister(RegisterEnum reg);

    bool getProcessorStatusWord(ProcessorStatusWordEnum psw);

    int getTicksPipe();

    int getTicksNoPipe();

    void reset();

private:
    ~Emulator();

    Emulator() = default;

    Emulator(Emulator const &emulator) = delete;

    Emulator &operator=(Emulator const &emulator) = delete;

    StateVariables emulator_state;

    Memory memory;

    Pipeline pipeline;

    std::stringstream assembly;
    std::vector<std::string> byteCode;

    void fetch();

    void decode();

    void loadOperands();

    void execute();


    uint16_t *pullOutAddress(uint8_t reg_num, uint8_t mode_num);

    std::string formatOperand(uint8_t reg_num, uint8_t mode_num);
};
