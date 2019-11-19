#include "pipeline"
#include <queue>

Pipeline& Pipeline::getInstance() {
    static Pipeline p;
    return p;
}

Pipeline::Pipeline():ticks(0), tasks(std::queue<Task>(0)) {
    // Some initializations
}

void Pipeline::addTicks() {
    this.ticks += defaultTicksAddCount;
}

void Pipeline::addTicks(const int count) {
    this.ticks += count;
}

void Pipeline::fetch(int pc) {
    // TODO:: Get instruction from memory[pc]
    // May be we need class Instruction
}

void Pipeline::decode() {
    // TODO:: translate received instruction to ... hz
}

void Pipeline::loadOpcode() {
    // TODO:: find opcode in opcode table
    // Yes, we need separated fucntion for this for integrity
}

void Pipeline::execute() {
    // TODO:: refresh everything: ticks, regs, mem
}

void Pipeline::storeRes() {
    // TODO:: Write in memory
}
