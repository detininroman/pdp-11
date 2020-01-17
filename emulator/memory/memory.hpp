#pragma once

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>


#include "../params.hpp"
#include "../error.hpp"

struct ProcessorStatusWord {
    bool N;
    bool Z;
    bool V;
    bool C;
};

enum ProcessorStatusWordEnum {
    PSW_N,
    PSW_Z,
    PSW_V,
    PSW_C
};

struct Registers {
    struct ProcessorStatusWord psw = {false, false, false, false};
    // General purpose registers.
    uint16_t r0;
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint16_t r4;
    uint16_t r5;
    uint16_t sp;  // Stack Pointer.
    uint16_t pc;  // Program Counter.
};

enum RegisterEnum {
    REG_R0,
    REG_R1,
    REG_R2,
    REG_R3,
    REG_R4,
    REG_R5,
    REG_SP,
    REG_PC
};

class Memory {
public:
    Memory(uint8_t *memory_dump, int len);

    Memory();

    ~Memory();

    Error getByteValue(uint16_t pos, uint8_t **val) const;

    Error setByteValue(uint16_t pos, uint8_t val);

    Error getWordAddress(uint16_t pos, uint16_t **val) const;

    Error setWordValue(uint16_t pos, uint16_t val);

    uint8_t *getByteAdress(uint16_t val) const;

    struct Registers registers;

    uint16_t *reg_table[8];

    Error init(uint8_t *memory_dump, int len);

    size_t getVideoMemory(uint8_t *buff, size_t size) const;

    size_t getROM(uint8_t *buff, size_t size) const;

private:
    uint8_t *memory_cells;
};
