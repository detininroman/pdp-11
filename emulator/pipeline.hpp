#pragma once

#include "instructions/instructions.hpp"

#include <map>
#include <queue>

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

    Error step();

private:
    int tick;
    int time_naive;
    int time_opt;
    vector<pair<PipelineStage, int>> instr_history;
    map<PipelineStage, queue<int>> backlog;
    map<PipelineStage, int> current_timers;
    vector<PipelineStage> devices;
};