#pragma once

#include <cstdint>
#include <string>

struct Instruction {
    /* Mask specifies how many first bits of 2B are related to the opcode. */
    uint16_t mask;
    uint16_t opcode;
    std::string name;

    void (*callback)();
};

void mov(void);

void sob(void);

void halt(void);