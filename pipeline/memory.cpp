#include "memory.h"
#include "../params.h"

Memory::Memory(size_t size) {
    memory_cells = new uint8_t[size];
}

Memory::~Memory() {
    delete memory_cells;
}

int Video::read(int pos, uint8_t &val) const{
    val = memory_cells[pos];
    return 0;
}

int Video::write(int pos, uint8_t val) {
    memory_cells[pos] = val;
    return 0;
}