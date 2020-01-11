#include <utility>
#include <algorithm>
#include "memory.hpp"

Memory::Memory(uint8_t* memory_dump, int len) {
    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE];
    // copying to ROM part
    memcpy(memory_cells + RAM_SIZE + VIDEO_SIZE, memory_dump, len);
}

Memory::~Memory() {
    delete memory_cells;
}

int Memory::getByteValue(uint16_t pos, uint8_t &val) const {
    val = memory_cells[pos];
}

int Memory::setByteValue(uint16_t pos, uint8_t val) {
    memory_cells[pos] = val;
}

int Memory::getWordValue(uint16_t pos, uint16_t &val) const {
    val = (uint16_t) memory_cells[pos];
}

int Memory::setWordValue(uint16_t pos, uint16_t val) {
    memset(memory_cells, val, 1);
}

uint8_t *Memory::getByteAdress(uint16_t pos) const {
    return &memory_cells[pos];
}