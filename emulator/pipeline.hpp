#pragma once

#include <map>
#include <queue>

#include "instructions/instructions.hpp"

using std::vector;
using std::pair;
using std::map;
using std::queue;

class Pipeline {
public:
    Pipeline();

    int getTicksOpt();

    int getTicksNaive();

    Error add(PipelineStage device, int command_ticks);

    Error count();

private:
    // TODO: Add Lock/Unlock with cache memory.
    int tick;
    int time_naive;
    int time_opt;
    vector<int> instr_history;
    map<PipelineStage, queue<int>> backlog;
    map<PipelineStage, int> current_timers;
    vector<PipelineStage> devices;
};
