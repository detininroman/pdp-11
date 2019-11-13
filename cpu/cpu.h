#pragma once
#include "../memory/memory.h"

class CPU{
public:
    // INSTRUCTIONS

private:
    uint16_t* reg[7];
    RAM RAM;
    VIDEO VRAM;
};