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

    Error add(CommandUnit device, int command_ticks);

    Error step();

private:
    int tick;
    int time_naive;
    int time_opt;
    vector<pair<CommandUnit, int>> instr_history;
    map<CommandUnit, queue<int>> backlog;
    map<CommandUnit, int> current_timers;
    vector<CommandUnit> devices;
};