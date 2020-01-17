#include "memory.hpp"

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
    memory_cells = new uint8_t[RAM_SIZE + VIDEO_SIZE + ROM_SIZE]();
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

Error Memory::getByteValue(uint16_t pos, uint8_t **val) const {
    if (pos > RAM_SIZE + VIDEO_SIZE + ROM_SIZE) {
        return Error::OUT_OF_BOUNDS;
    }
    *val = &memory_cells[pos];
    return Error::OK;
}

Error Memory::setByteValue(uint16_t pos, uint8_t val) {
    if (pos > RAM_SIZE + VIDEO_SIZE + ROM_SIZE) {
        return Error::OUT_OF_BOUNDS;
    }
    memory_cells[pos] = val;
    return Error::OK;
}

Error Memory::getWordAddress(uint16_t pos, uint16_t **val) const {
    if (pos % 2) {
        throw std::runtime_error(
                "Address must be even if you want to get whole word");
    }

    if (pos > RAM_SIZE + VIDEO_SIZE + ROM_SIZE) {
        return Error::OUT_OF_BOUNDS;
    }
    *val = (uint16_t *) &memory_cells[pos];
    return Error::OK;
}

Error Memory::setWordValue(uint16_t pos, uint16_t val) {
    memset(memory_cells, val, 1);
    return Error::OK;
}

uint8_t *Memory::getByteAdress(uint16_t pos) const {
    if (pos > RAM_SIZE + VIDEO_SIZE + ROM_SIZE) {
        return nullptr;  // Take care
    }
    return &memory_cells[pos];
}

size_t Memory::getVideoMemory(uint8_t *buff, size_t size) const {
    size_t actual_size = size < VIDEO_SIZE ? size : VIDEO_SIZE;
    memcpy(buff, memory_cells + RAM_SIZE, actual_size);
    return actual_size;
}

size_t Memory::getROM(uint8_t *buff, size_t size) const {
    size_t actual_size = size < ROM_SIZE ? size : ROM_SIZE;
    memcpy(buff, memory_cells + RAM_SIZE + VIDEO_SIZE, actual_size);
    return actual_size;
}

void Memory::cleanVideoMemory() {
    memcpy(memory_cells + RAM_SIZE, 0, VIDEO_SIZE);
}