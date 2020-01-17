#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../memory/memory.hpp"
#include "../error.hpp"

enum class PipelineStage {
    FETCH_STAGE,
    DECODE_STAGE,
    EXECUTE_STAGE, // If you add any new units, please init queue for them in pipeline class
    MEMORY_ACCESS_STAGE,
    WRITE_BACK_STAGE,
};


enum class InstructionType {
    DOUBLE_OPERAND,
    DOUBLE_OPERAND_REG,
    SINGLE_OPERAND,
    CONDITIONAL_BRANCH,
    NO_OPERAND,
};

struct Instruction {
    /* Mask specifies how many first bits of 2B are related to the opcode. */
    uint16_t mask;
    uint16_t opcode;
    std::string name;
    InstructionType type;

    Error (*callback)(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);
};

Error mov(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error cmp(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error add(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error sub(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error mul(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error div(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error xor_(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error sob(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error clr(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error inc(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error dec(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

Error halt(struct Registers *registers, uint16_t *operand1, uint16_t *operand2);

const std::vector<struct Instruction> kInstructionTable = {
        {0xf000, 0x1000, "mov",  InstructionType::DOUBLE_OPERAND,     mov},
//      {0xf000, 0x9000, "movb", InstructionType::DOUBLE_OPERAND,     movb},
        {0xf000, 0x2000, "cmp",  InstructionType::DOUBLE_OPERAND,     cmp},
/*
        {0xf000, 0xa000, "cmpb", InstructionType::DOUBLE_OPERAND,     cmpb},
        {0xf000, 0x3000, "bit",  InstructionType::DOUBLE_OPERAND,     bit},
        {0xf000, 0xb000, "bitb", InstructionType::DOUBLE_OPERAND,     bitb},
        {0xf000, 0x4000, "bic",  InstructionType::DOUBLE_OPERAND,     bic},
        {0xf000, 0xc000, "bicb", InstructionType::DOUBLE_OPERAND,     bicb},
        {0xf000, 0x5000, "bis",  InstructionType::DOUBLE_OPERAND,     bis},
        {0xf000, 0xd000, "bisb", InstructionType::DOUBLE_OPERAND,     bisb},
*/
        {0xf000, 0x6000, "add",  InstructionType::DOUBLE_OPERAND,     add},
        {0xf000, 0xe000, "sub",  InstructionType::DOUBLE_OPERAND,     sub},

        {0xfe00, 0x7000, "mul",  InstructionType::DOUBLE_OPERAND_REG, mul},
        {0xfe00, 0x7200, "div",  InstructionType::DOUBLE_OPERAND_REG, div},
//      {0xfe00, 0x7400, "ash",  InstructionType::DOUBLE_OPERAND_REG, ash},
//      {0xfe00, 0x7600, "ashc", InstructionType::DOUBLE_OPERAND_REG, ashc},
        {0xfe00, 0x7800, "xor",  InstructionType::DOUBLE_OPERAND_REG, xor_},
        {0xfe00, 0x7e00, "sob",  InstructionType::DOUBLE_OPERAND_REG, sob},

//      {0xffc0, 0x00c0, "swab", InstructionType::SINGLE_OPERAND,     swab},
        {0xffc0, 0x0a00, "clr",  InstructionType::SINGLE_OPERAND,     clr},
/*
        {0xffc0, 0x8a00, "clrb", InstructionType::SINGLE_OPERAND,     clrb},
        {0xffc0, 0x0a40, "com",  InstructionType::SINGLE_OPERAND,     com},
        {0xffc0, 0x8a40, "comb", InstructionType::SINGLE_OPERAND,     comb},
*/
        {0xffc0, 0x0a80, "inc",  InstructionType::SINGLE_OPERAND,     inc},
//      {0xffc0, 0x8a80, "incb", InstructionType::SINGLE_OPERAND,     incb},
        {0xffc0, 0x0ac0, "dec",  InstructionType::SINGLE_OPERAND,     dec},
/*
        {0xffc0, 0x8ac0, "decb", InstructionType::SINGLE_OPERAND,     decb},
        {0xffc0, 0x0b00, "neg",  InstructionType::SINGLE_OPERAND,     neg},
        {0xffc0, 0x8b00, "negb", InstructionType::SINGLE_OPERAND,     negb},
        {0xffc0, 0x0b40, "adc",  InstructionType::SINGLE_OPERAND,     adc},
        {0xffc0, 0x8b40, "adcb", InstructionType::SINGLE_OPERAND,     adcb},
        {0xffc0, 0x0b80, "sbc",  InstructionType::SINGLE_OPERAND,     sbc},
        {0xffc0, 0x8b80, "sbcb", InstructionType::SINGLE_OPERAND,     sbcb},
        {0xffc0, 0x0bc0, "tst",  InstructionType::SINGLE_OPERAND,     tst},
        {0xffc0, 0x8bc0, "tstb", InstructionType::SINGLE_OPERAND,     tstb},
        {0xffc0, 0x0c00, "ror",  InstructionType::SINGLE_OPERAND,     ror},
        {0xffc0, 0x8c00, "rorb", InstructionType::SINGLE_OPERAND,     rorb},
        {0xffc0, 0x0c40, "rol",  InstructionType::SINGLE_OPERAND,     rol},
        {0xffc0, 0x8c40, "rolb", InstructionType::SINGLE_OPERAND,     rolb},
        {0xffc0, 0x0c80, "asr",  InstructionType::SINGLE_OPERAND,     asr},
        {0xffc0, 0x8c80, "asrb", InstructionType::SINGLE_OPERAND,     asrb},
        {0xffc0, 0x0cc0, "asl",  InstructionType::SINGLE_OPERAND,     asl},
        {0xffc0, 0x8cc0, "aslb", InstructionType::SINGLE_OPERAND,     aslb},
        {0xffc0, 0x0d00, "mark", InstructionType::SINGLE_OPERAND,     mark},
        {0xffc0, 0x8d00, "mtps", InstructionType::SINGLE_OPERAND,     mtps},
        {0xffc0, 0x0d40, "mfpi", InstructionType::SINGLE_OPERAND,     mfpi},
        {0xffc0, 0x8d40, "mfpd", InstructionType::SINGLE_OPERAND,     mfpd},
        {0xffc0, 0x0d80, "mtpi", InstructionType::SINGLE_OPERAND,     mtpi},
        {0xffc0, 0x8d80, "mtpd", InstructionType::SINGLE_OPERAND,     mtpd},
        {0xffc0, 0x0dc0, "sxt",  InstructionType::SINGLE_OPERAND,     sxt},
        {0xffc0, 0x8dc0, "mfps", InstructionType::SINGLE_OPERAND,     mfps},
*/
        {0xffc0, 0x0000, "halt", InstructionType::NO_OPERAND,         halt},
};
