#pragma once

#include "error.hpp"
#include "instructions/instructions.hpp"
#include "pipeline.hpp"

class Action {
public:
    Action() = default;

    Action(Pipeline &p_o, CommandUnit d, int t,
           Error (*callback)(struct Registers *registers, uint16_t *operand1, uint16_t *operand2)) : device(d),
                                                                                                     ticks(t) {
        instruction_function = callback;
        service_function = nullptr;
    }

    Action(Pipeline &p_o, CommandUnit d, int t, Error (*callback)()) : device(d), ticks(t) {
        service_function = callback;
        instruction_function = nullptr;
    }

    Error execute(Pipeline &pipeline_object, struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
        if (!instruction_function) {
            return Error::NOT_INITED;
        }
        pipeline_object.add(device, ticks);
        return instruction_function(registers, operand1, operand2);
    }

    Error execute(Pipeline &pipeline_object) {
        if (!service_function) {
            return Error::NOT_INITED;
        }
        pipeline_object.add(device, ticks);
        return service_function();
    }

private:
    CommandUnit device;
    int ticks;

    Error (*instruction_function)(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

    Error (*service_function)();
};