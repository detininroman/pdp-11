#pragma once

#include "../params.hpp"

#include <cstdint>
#include <cstdio>

struct ProcessorStatusWord {
    bool N;
    bool Z;
    bool V;
    bool C;
};

struct Registers {
    struct ProcessorStatusWord psw = {0};
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
    Memory(uint16_t size);

    ~Memory();

    virtual int getByteValue(uint16_t pos, uint8_t &val) const = 0;

    virtual int setByteValue(uint16_t pos, uint8_t val) = 0;

    virtual int getWordValue(uint16_t pos, uint16_t &val) const = 0;

    virtual int setWordValue(uint16_t pos, uint16_t val) = 0;

    virtual uint8_t *getByteAdress(uint16_t pos) const = 0;

    struct Registers registers;

protected:
    uint8_t *memory_cells;
};

class RAM : Memory {
public:
    RAM() : Memory(RAM_SIZE) {};

    int getByteValue(uint16_t pos, uint8_t &val) const;

    int setByteValue(uint16_t pos, uint8_t val);

    int getWordValue(uint16_t pos, uint16_t &val) const;

    int setWordValue(uint16_t pos, uint16_t val);

    uint8_t *getByteAdress(uint16_t pos) const;
};

class Video : Memory { // every p
public:
    Video() : Memory(VIDEO_SIZE) {};

    int getByteValue(uint16_t pos, uint8_t &val) const;

    int setByteValue(uint16_t pos, uint8_t val);

    int getWordValue(uint16_t pos, uint16_t &val) const;

    int setWordValue(uint16_t pos, uint16_t val);

    uint8_t *getByteAdress(uint16_t pos) const;
};

class Reg : Memory {
public:
    Reg() : Memory(REG_SIZE) {};

    int getByteValue(uint16_t pos, uint8_t &val) const;

    int setByteValue(uint16_t pos, uint8_t val);

    int getWordValue(uint16_t pos, uint16_t &val) const;

    int setWordValue(uint16_t pos, uint16_t val);

    uint8_t *getByteAdress(uint16_t pos) const;
};
