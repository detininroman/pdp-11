#pragma once

#include <queue>
#include "../cpu/cpu.h"

class Pipeline {
public:
    void addTicks();
    void addTicks(int);
    Pipeline& getInstance();
private:
    // TODO:: fill parameters and types and may be replace something in public
    // pc - program counter
    void fetch(int pc);
    void decode(/*?*/);
    void loadOpcode(/*?*/);
    void execute(/*?*/);
    void storeRes(/*?*/);

    // We have a singleton // <----- Should consider Emulator class, which controls pipeline state, steps and interacts with GUI
    void Pipeline();
    void ~Pipeline();
    Pipeline(Pipeline const&) = delete;
    Pipeline& operator= (Pipeline const&) = delete;

    int ticks; // <----- Should also be moved into External class, as we need to externaly control emulator state
    // TODO:: change according to real data
    const int defaultTicksAddCount = 50;
    std::queue<Task> tasks;
    CPU CPU;
}
