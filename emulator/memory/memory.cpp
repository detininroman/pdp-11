#include "memory.hpp"

Memory::Memory(uint16_t size): memory_cells(new uint8_t[size]) {}

Memory::~Memory() {
    delete memory_cells;
}

int RAM::getByteValue(uint16_t pos, uint8_t &val) const {
    val = memory_cells[pos];
}

int RAM::setByteValue(uint16_t pos, uint8_t val) {
    memory_cells[pos] = val;
}

int RAM::getWordValue(uint16_t pos, uint16_t &val) const {

}

int RAM::setWordValue(uint16_t pos, uint16_t val) {

}

uint8_t* RAM::getByteAdress(uint16_t pos) const {
    return &memory_cells[pos];
}

// Just for compiling at the moment:
//-----------------------------------------------------------------------------

int Video::getByteValue(uint16_t pos, uint8_t &val) const {
    val = memory_cells[pos];
}

int Video::setByteValue(uint16_t pos, uint8_t val) {
    memory_cells[pos] = val;
}

int Video::getWordValue(uint16_t pos, uint16_t &val) const {

}

int Video::setWordValue(uint16_t pos, uint16_t val) {

}

uint8_t* Video::getByteAdress(uint16_t pos) const {
    return &memory_cells[pos];
}

//-----------------------------------------------------------------------------

int Reg::getByteValue(uint16_t pos, uint8_t &val) const {
    val = memory_cells[pos];
}

int Reg::setByteValue(uint16_t pos, uint8_t val) {
    memory_cells[pos] = val;
}

int Reg::getWordValue(uint16_t pos, uint16_t &val) const {

}

int Reg::setWordValue(uint16_t pos, uint16_t val) {

}

uint8_t *Reg::getByteAdress(uint16_t pos) const {
    return &memory_cells[pos];
}

