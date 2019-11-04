#include "memory.h"
#include "params.h"

Memory::Memory(size_t size) {
    memory_cells = new char[size];
}

Memory::~Memory() {
    delete memory_cells;
}

int Video::read(int pos, char &val) const{
    val = memory_cells[pos];
    return 0;
}

int Video::write(int pos, char val) {
    memory_cells[pos] = val;
    return 0;
}