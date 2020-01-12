#include <utility>
#include <algorithm>

#include "memory.hpp"

Memory::Memory() {
    //  Zero inited.
    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE]();
}

Memory::Memory(uint8_t *memory_dump, int len) {
    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE];
    // Copying to ROM part.
    memcpy(memory_cells + RAM_SIZE + VIDEO_SIZE, memory_dump, len);
}

Error Memory::init(uint8_t *memory_dump, int len) {
    // Copying to ROM part.
    memcpy(memory_cells + RAM_SIZE + VIDEO_SIZE, memory_dump, len);
    return Error::OK;
}

Memory::~Memory() {
    delete memory_cells;
}

Error Memory::getByteValue(uint16_t pos, uint8_t &val) const {
    val = memory_cells[pos];
    return Error::OK;
}

Error Memory::setByteValue(uint16_t pos, uint8_t val) {
    memory_cells[pos] = val;
    return Error::OK;
}

Error Memory::getWordValue(uint16_t pos, uint16_t &val) const {
    if (pos % 2) {
        throw std::runtime_error(
                "Address must be even if you want to get whole word");
    }
    // returning in BigEndian, while we store in LittleEndian
    val = (memory_cells[pos + 1] << 8) || (memory_cells[pos] >> 8);
    return Error::OK;
}

Error Memory::setWordValue(uint16_t pos, uint16_t val) {
    memset(memory_cells, val, 1);
    return Error::OK;
}

uint8_t *Memory::getByteAdress(uint16_t pos) const {
    return &memory_cells[pos];
}

size_t Memory::getVideoMemory(uint8_t *buff, size_t size) const {
    size_t actual_size = size < VIDEO_SIZE ? size : VIDEO_SIZE;
    memcpy(buff, memory_cells + RAM_SIZE, actual_size);
    return actual_size;
}