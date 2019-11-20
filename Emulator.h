#pragma once

#include "memory/memory.h"
#include "pipeline/pipeline.h"

class Emulator {
public:
    Emulator(); // <---- can run this as a singletone
    void addTicks();

    void addTicks(int);

    uint8_t getVideo() const;
    // INSTRUCTIONS
private:
    int ticks;
    // TODO:: change according to real data
    const int defaultTicksAddCount = 50;
    Pipeline line;
};
