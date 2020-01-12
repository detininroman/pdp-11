#pragma once

#include <cstdint>
#include <string>

#include "../memory/memory.hpp"

enum class InstructionType {
    DOUBLE_OPERAND,
    DOUBLE_OPERAND_REG,
    SINGLE_OPERAND,
    CONDITIONAL,
    NO_OPERAND,
};

struct Instruction {
    /* Mask specifies how many first bits of 2B are related to the opcode. */
    uint16_t mask;
    uint16_t opcode;
    std::string name;
    InstructionType type;

    void (*callback)(struct Registers *registers, uint16_t *operand1,
                     uint16_t *operand2);
};

void mov(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

void sob(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

void halt(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);