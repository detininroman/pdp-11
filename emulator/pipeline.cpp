#include "pipeline.hpp"


Pipeline::Pipeline() {
    // add more devices if needed
    devices.push_back(CommandUnit::ALU);
    devices.push_back(CommandUnit::FETCH_UNIT);
    devices.push_back(CommandUnit::DECODE_UNIT);

    for (auto &device : devices) {
        backlog[device] = queue<int>();
        current_timers[device] = 0;
    }
    tick = 0;
    time_naive = 0;
    time_opt = 0;
}

Error Pipeline::add(CommandUnit device, int command_ticks) {
    if (!backlog.count(device)) {
        return Error::UNKNOWN_DEVICE;
    }
    backlog[device].push(command_ticks);
    instr_history.emplace_back(std::make_pair(device, command_ticks));
    return Error::OK;
}


Error Pipeline::step() {
    bool finished = true;

    if (!instr_history.empty()) {
        time_naive += instr_history.back().second;
        instr_history.pop_back();
    }

    for (auto &device : devices) { // iterating over all devices for pipelined execution
        if (current_timers[device]) { //device is busy
            --current_timers[device];
            continue;
        }
        if (backlog[device].empty()) { // no commands for this device yet
            continue;
        }
        current_timers[device] = backlog[device].front(); // have something for device
        backlog[device].pop();
        finished = false;
    }
    if (finished) {
        return Error::EMPTY_BACKLOG;
    }
    tick += 1;
    time_opt += 1;

    return Error::OK;
}

int Pipeline::getTicksOpt() {
    while(step() == Error::OK);
    return time_opt;
}

int Pipeline::getTicksNaive() {
    while (!instr_history.empty()) {
        time_naive += instr_history.back().second;
        instr_history.pop_back();
    }

    return time_naive;
}
