#pragma once
#include <cstdio>
#include "params.h"

class MemoryDispatcher{
    //interface to address any type of memory
};

class Memory{
public:
    Memory(size_t size);
    ~Memory();
    virtual int write(int pos, char val) = 0;
    virtual int read(int pos, char& val) = 0;
protected:
    char* memory_cells;
};

class RAM : Memory{
public:
    RAM() : Memory(RAM_SIZE) {};
    int write(int pos, char val);
    int read(int pos, char& val);
};

class Video : Memory{
public:
    Video() : Memory(VIDEO_SIZE) {};
    int write(int pos, char val);
    int read(int pos, char& val) const;
};

class Commands : Memory{
public:
    Commands() : Memory(COMMAND_SIZE) {};
    int write(int pos, char val);
    int read(int pos, char& val);
};