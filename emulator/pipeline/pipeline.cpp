#include<numeric>

#include "pipeline.hpp"

Pipeline::Pipeline() {
    // Add more devices if needed
    devices.push_back(PipelineStage::FETCH_STAGE);
    devices.push_back(PipelineStage::DECODE_STAGE);
    devices.push_back(PipelineStage::EXECUTE_STAGE);
    devices.push_back(PipelineStage::MEMORY_ACCESS_STAGE);
    devices.push_back(PipelineStage::WRITE_BACK_STAGE);

    for (auto &device : devices) {
        backlog[device] = queue<int>();
        current_timers[device] = 0;
    }
    tick = 0;
    time_naive = 0;
    time_opt = 0;
}

Error Pipeline::add(PipelineStage device, int command_ticks) {
    if (!backlog.count(device)) {
        return Error::UNKNOWN_DEVICE;
    }
    backlog[device].push(command_ticks);
    instr_history.emplace_back(command_ticks);
    return Error::OK;
}

Error Pipeline::count() {
    bool finished = false;
    while (!finished) {
        finished = true;

        time_opt++;
        for (auto &device : devices) { // Iterating over all devices for pipelined execution
            if (current_timers[device]) { // Device is busy
                --current_timers[device];
                continue;
            }
            if (backlog[device].empty()) {  // No commands for this device yet
                continue;
            }
            current_timers[device] = backlog[device].front();  // Have something for device
            backlog[device].pop();
            finished = false;
        }
    }
    return Error::OK;
}

int Pipeline::getTicksOpt() {
    return time_opt;
}

int Pipeline::getTicksNaive() {
    time_naive += accumulate(instr_history.begin(), instr_history.end(), 0);
    instr_history.clear();
    while (!instr_history.empty()) {
        time_naive += instr_history.back();
        instr_history.pop_back();
    }
    return time_naive;
}
