#pragma once
#include <cstdio>
#include <cstdint>
#include "../params.h"

class MemoryDispatcher{
    //interface to address any type of memory
};

class Memory{
public:
    Memory(size_t size);
    ~Memory();
    virtual int write(uint8_t pos, uint8_t val) = 0;
    virtual int read(uint8_t pos, uint8_t& val) = 0;
protected:
    uint8_t* memory_cells;
};

class RAM : Memory{
public:
    RAM() : Memory(RAM_SIZE) {};
    int write(int pos, uint8_t val);
    int read(int pos, uint8_t& val);
};

class Video : Memory{
public:
    Video() : Memory(VIDEO_SIZE) {};
    int write(int pos, uint8_t val);
    int read(int pos, uint8_t& val) const;
};

class Commands : Memory{
public:
    Commands() : Memory(COMMAND_SIZE) {};
    int write(int pos, uint8_t val);
    int read(int pos, uint8_t& val);
};