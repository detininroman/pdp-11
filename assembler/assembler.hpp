#pragma once

#include <cstdint>
#include <iostream>
#include <vector>


class Assembler {
public:
    std::vector<uint16_t> parseStream(std::istream &str);

    std::vector<uint16_t> parseString(const std::string &str);

    std::vector<uint16_t> instructionToBinary(const std::vector<std::string> &instruction);

    void generateBinary(std::istream &in, const char *out_file);

    void generateHumanReadable(std::istream &in, const char *out_file);
};
