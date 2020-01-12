#include <utility>
#include <algorithm>

#include "memory.hpp"
#include "../error.hpp"

Memory::Memory() {
    //  Zero inited.
    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE]();
}

Memory::Memory() {
    reg_table[0] = &registers.r0;
    reg_table[1] = &registers.r1;
    reg_table[2] = &registers.r2;
    reg_table[3] = &registers.r3;
    reg_table[4] = &registers.r4;
    reg_table[5] = &registers.r5;
    reg_table[6] = &registers.sp;
    reg_table[7] = &registers.pc;

    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE]();
}
Memory::Memory(uint8_t *memory_dump, int len) {
    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE];
    // Copying to ROM part.
    memcpy(memory_cells + RAM_SIZE + VIDEO_SIZE, memory_dump, len);
}

int Memory::init(uint8_t *memory_dump, int len) {
    // Copying to ROM part.
    memcpy(memory_cells + RAM_SIZE + VIDEO_SIZE, memory_dump, len);
    return ERROR_OK;
}

Memory::~Memory() {
    delete memory_cells;
}

int Memory::getByteValue(uint16_t pos, uint8_t &val) const {
    val = memory_cells[pos];
    return ERROR_OK;
}

int Memory::setByteValue(uint16_t pos, uint8_t val) {
    memory_cells[pos] = val;
    return ERROR_OK;
}

int Memory::getWordValue(uint16_t pos, uint16_t &val) const {
    if (pos % 2) {
        throw std::runtime_error(
                "Address must be even if you want to get whole word");
    }
    // returning in BigEndian, while we store in LittleEndian
    val = (memory_cells[pos + 1] << 8) || (memory_cells[pos] >> 8);
    return ERROR_OK;
}

int Memory::setWordValue(uint16_t pos, uint16_t val) {
    memset(memory_cells, val, 1);
    return ERROR_OK;
}

uint8_t *Memory::getByteAdress(uint16_t pos) const {
    return &memory_cells[pos];
}

size_t Memory::getVideoMemory(uint8_t *buff, size_t size) const {
    size_t actual_size = size < VIDEO_SIZE ? size : VIDEO_SIZE;
    memcpy(buff, memory_cells + RAM_SIZE, actual_size);
    return actual_size;
}