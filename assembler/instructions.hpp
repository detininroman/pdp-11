#pragma once

struct Instruction {
    std::string name;
    short operands;
    uint16_t opcode;  // Octal number system
    bool allow_literal;
    bool double_operand_reg;
};

const std::unordered_map <std::string, Instruction> kInstructions{
        {"mov", {"mov", 2, 001, true, false}},
        {"movb", {"movb", 2, 011, true, false}},
        {"cmp", {"cmp", 2, 002, true, false}},
        {"cmpb", {"cmpb", 2, 012, true, false}},
        {"add", {"add", 2, 006, true, false}},
        {"sub", {"sub", 2, 016, true, false}},
        {"inc", {"inc", 1, 0052, false, false}},
        {"halt", {"halt", 0, 0, false, false}},
        {"mul", {"mul", 2, 070, true, false}},
        {"div", {"div", 2, 071, true, false}},
        {"clr", {"clr", 1, 50, false, false}},
        {"xor", {"xor", 2, 074, true, true}},
        {"sob", {"sob", 2, 077, true, true}},
        {"dec", {"dec", 1, 0053, false, false}},
};
