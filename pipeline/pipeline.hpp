#pragma once
#include "../cpu/cpu.h"
#include <queue>

class Pipeline {
public:
    Pipeline &getInstance();
    int getCurrentState();
    void makeStep(); // call this from CPU to perform one operation
private:
    // TODO:: fill parameters and types and may be replace something in public
    // pc - program counter
    void fetch(int pc);
    void decode(/*?*/);
    void loadOpcode(/*?*/);
    void execute(/*?*/);
    void storeRes(/*?*/);
    int stage; //Fetch/Decode/Execute/WriteBack

    Pipeline(Pipeline const&) = delete;
    Pipeline& operator= (Pipeline const&) = delete;
    std::queue<Task> tasks;
};

