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
    ticks += defaultTicksAddCount;
}

void Pipeline::addTicks(const int count) {
    ticks += count;
}
