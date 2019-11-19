#pragma once
#include "../memory/memory.h"
#include "../pipeline/pipeline.hpp"

class CPU{
public:
    CPU(); // <---- can run this as singletone
    void addTicks();
    void addTicks(int);
    // INSTRUCTIONS
private:
    int ticks;
    // TODO:: change according to real data
    const int defaultTicksAddCount = 50;
    Pipeline line;
    uint16_t *reg[7];
    RAM RAM;
    VIDEO VRAM;
};
