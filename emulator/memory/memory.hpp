#pragma once

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "../params.hpp"
#include "../error.hpp"

struct ProcessorStatusWord {
    bool N;
    bool Z;
    bool V;
    bool C;
};

struct Registers {
    struct ProcessorStatusWord psw =
            {false, false, false, false};
    // General purpose registers.
    uint16_t r0;
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint16_t r4;
    uint16_t r5;
    uint16_t sp; //  Stack Pointer.
    uint16_t pc; //  Program Counter.
};


class Memory {
public:
    Memory(uint8_t *memory_dump, int len);

    Memory();

    ~Memory();

    Error getByteValue(uint16_t, uint8_t &) const;

    Error setByteValue(uint16_t, uint8_t);

    Error getWordValue(uint16_t, uint16_t &) const;

    Error setWordValue(uint16_t, uint16_t);

    uint8_t *getByteAdress(uint16_t) const;

    struct Registers registers;

    Error init(uint8_t *memory_dump, int len);

    size_t getVideoMemory(uint8_t *buff, size_t size) const;

private:

    uint8_t *memory_cells;

};