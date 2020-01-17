#include <regex>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <stdio.h>

#include "assembler.hpp"
#include "instructions.hpp"

struct Operand {
    uint8_t mode;
    uint8_t reg;
    uint16_t ref;

    uint8_t to_bits() {
        return (mode << 3) | reg;
    }
};

const Operand kLiteralOperand = {2, 7, 0};

static bool isLiteral(const std::string &op) {
    if (op.find("0x") == 0) {
        auto predicate = [](char c) {
            return (std::isdigit(c) || (c >= 'a' && c <= 'f'));
        };
        return std::all_of(op.begin() + 2, op.end(), predicate);
    }
    short shift = op[0] == '-' ? 1 : 0;
    return !op.empty() && std::all_of(op.begin() + shift, op.end(), ::isdigit);
}

const std::vector<std::regex> kAddrModeRegex{
        std::regex("r(\\d)"),
        std::regex("\\(r(\\d)\\)"),
        std::regex("\\(r(\\d)\\)\\+"),
        std::regex("@\\(r(\\d)\\)\\+"),
        std::regex("-\\(r(\\d)\\)"),
        std::regex("@-\\(r(\\d)\\)"),
        std::regex("(\\d+|0x[\\dA-Fa-f]+)\\(r(\\d)\\)"),
        std::regex("@(\\d+|0x[\\dA-Fa-f]+)\\(r(\\d)\\)"),
};

static std::vector<std::vector<std::string>> tokenizeFile(std::istream &input) {
    std::vector<std::vector<std::string>> result;
    while (!input.eof()) {
        std::vector<std::string> command{""};
        std::string line;
        std::getline(input, line);
        for (char c : line) {
            if (c == ';' || command.size() > 3) {
                break;
            } else if (c == ' ') {
                if (!command.back().empty()) {
                    command.emplace_back();
                }
            } else {
                command.back() += c;
            }
        }
        if (command.back().empty()) {
            command.pop_back();
        }
        if (!command.empty()) {
            result.push_back(std::move(command));
        }
    }
    return result;
}

static Operand parseOperand(const std::string &op) {
    std::smatch match;
    Operand result;
    for (int i = 0; i < kAddrModeRegex.size(); ++i) {
        if (std::regex_match(op, match, kAddrModeRegex[i])) {
            result.mode = i;
            break;
        }
    }
    if (match.empty()) {
        throw std::runtime_error("Invalid operand " + op);
    }
    if (result.mode == 6 || result.mode == 7) {
        result.ref = std::stoi(match[1], 0, 0);
        result.reg = std::stoi(match[2], 0);
    } else {
        result.reg = std::stoi(match[1], 0);
    }
    return result;
}

std::vector<uint16_t> Assembler::instructionToBinary(const std::vector<std::string> &instruction) {
    if (isLiteral(instruction[0])) {
        return {static_cast<uint16_t>(std::stoi(instruction[0], 0, 0))};
    }
    if (kInstructions.find(instruction[0]) == kInstructions.end()) {
        throw std::runtime_error("Invalid instruction " + instruction[0]);
    }

    const Instruction &instr = kInstructions.at(instruction[0]);

    if (instruction.size() != instr.operands + 1) {
        throw std::runtime_error("Wrong operand count for " + instr.name);
    }

    if (instr.operands == 0) {
        return {instr.opcode};
    }

    std::vector<uint16_t> result = {0};
    Operand first_operand;

    if (isLiteral(instruction[1])) {
        if (!instr.allow_literal) {
            throw std::runtime_error("Instruction does not allow literals");
        }

        first_operand = kLiteralOperand;
        result.push_back(static_cast<int16_t>(std::stoi(instruction[1], 0, 0)));
    } else {
        first_operand = parseOperand(instruction[1]);
        if (first_operand.mode == 6 || first_operand.mode == 7) {
            result.push_back(first_operand.ref);
        }
    }

    if (instr.operands == 1) {
        result[0] = (instr.opcode << 6) | first_operand.to_bits();
        return result;
    }

    /*    Operand second_operand = parseOperand(instruction[2]);
        if (second_operand.mode == 6 || second_operand.mode == 7) {
            result.push_back(second_operand.ref);
        }
        result[0] = (instr.opcode << 12) | (first_operand.to_bits() << 6) |
                    (second_operand.to_bits());
    */

    Operand second_operand;
    if (isLiteral(instruction[2])) {
        if (!instr.allow_literal) {
            throw std::runtime_error("Instruction does not allow literals");
        }

        second_operand = kLiteralOperand;
        result.push_back(static_cast<int16_t>(std::stoi(instruction[2], 0, 0)));
    } else {
        second_operand = parseOperand(instruction[2]);
        if (second_operand.mode == 6 || second_operand.mode == 7) {
            result.push_back(second_operand.ref);
        }
    }

    if (instr.double_operand_reg) {
        result[0] = (instr.opcode << 9) | (first_operand.to_bits() << 6) | (second_operand.to_bits());
    } else {
        result[0] = (instr.opcode << 12) | (first_operand.to_bits() << 6) | (second_operand.to_bits());
    }

    return result;
}

std::vector<uint16_t> Assembler::parseStream(std::istream &str) {
    std::vector<std::vector<std::string>> tokens = tokenizeFile(str);

    std::vector<uint16_t> result;
    for (auto instruction : tokens) {
        if (instruction[0] == "#") {
            continue;
        }
        for (auto oct : instructionToBinary(instruction)) {
            result.push_back(oct);
        }
    }

    return result;
}

std::vector<uint16_t> Assembler::parseString(const std::string &str) {
    std::istringstream stream(str);
    return parseStream(stream);
}

void Assembler::generateBinary(std::istream &str, const char *out_file) {
    auto result = parseStream(str);

    FILE *out;
    out = fopen(out_file, "wb");
    for (auto &word : result) {
        fwrite(&word, 2, 1, out);
    }

    fclose(out);
}

void Assembler::generateHumanReadable(std::istream &in, const char *out_file) {
    auto result = parseStream(in);
    // Big -> Little endian
    for (auto &word : result) {
        uint8_t tmp = word >> 8;
        word = (word << 8) | tmp;
    }

    std::ofstream out_stream(out_file);
    for (auto &word : result) {
        out_stream << std::hex << word << ' ';
    }
}
