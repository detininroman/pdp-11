#pragma once
#include "../params.h"
#include <cstdio>
#include <cstdint>
#include <bits/shared_ptr.h>

using std::shared_ptr;

typedef enum memory_types{
    RAM_MEMORY,
    VRAM_MEMORY,
    REG_MEMORY
} MEMORY_TYPE;


class Memory{
public:
    Memory(uint16_t size);
    ~Memory();
    virtual int getByteValue(uint16_t pos, uint8_t &val) const = 0;
    virtual int setByteValue(uint16_t pos, uint8_t val) = 0;
    virtual int getWordValue(uint16_t pos, uint16_t &val) const = 0;
    virtual int setWordValue(uint16_t pos, uint16_t val) = 0;
    virtual uint8_t *getByteAdress(uint16_t pos) const = 0;
protected:
    uint8_t* memory_cells;
};

class RAM : Memory{
public:
    RAM() : Memory(RAM_SIZE) {};
    int getByteValue(uint16_t pos, uint8_t &val) const;
    int setByteValue(uint16_t pos, uint8_t val);
    int getWordValue(uint16_t pos, uint16_t &val) const;
    int setWordValue(uint16_t pos, uint16_t val);
    uint8_t *getByteAdress(uint16_t pos) const;
};

class Video : Memory{
public:
    Video() : Memory(VIDEO_SIZE) {};
    int getByteValue(uint16_t pos, uint8_t &val) const;
    int setByteValue(uint16_t pos, uint8_t val);
    int getWordValue(uint16_t pos, uint16_t &val) const;
    int setWordValue(uint16_t pos, uint16_t val);
    uint8_t *getByteAdress(uint16_t pos) const;
};

class Reg : Memory{
public:
    Reg() : Memory(COMMAND_SIZE) {};
    int getByteValue(uint16_t pos, uint8_t &val) const;
    int setByteValue(uint16_t pos, uint8_t val);
    int getWordValue(uint16_t pos, uint16_t &val) const;
    int setWordValue(uint16_t pos, uint16_t val);
    uint8_t* getByteAdress(uint16_t pos) const;
};

class MemoryDispatcher {
    //maybe we shoukd consider interface to address any type of memory
    MemoryDispatcher(MEMORY_TYPE type);
public:
    uint16_t getMemValue(uint16_t address);
    uint16_t *getMemAddr(uint16_t address);
private:
    shared_ptr<Memory> device;
};
