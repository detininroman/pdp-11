#pragma once

#include <cstdint>
#include <string>

#include "../memory/memory.hpp"
#include "../error.hpp"

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

    Error (*callback)(struct Registers *registers, uint16_t *operand1,
                      uint16_t *operand2);
};

Error mov(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error cmp(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error add(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error sub(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error mul(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error div(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error sob(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error halt(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);