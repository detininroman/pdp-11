#include "memory.h"
#include "../params.h"

Memory::Memory(uint16_t size) {
    memory_cells = new uint8_t[size];
}

Memory::~Memory() {
    delete memory_cells;
}

int RAM::setByteValue(uint16_t pos, uint8_t val){
    memory_cells[pos] = val;
}

int RAM::setWordValue(uint16_t pos, uint16_t val){

}

int RAM::getByteValue(uint16_t pos, uint8_t& val) const{
    val = memory_cells[pos];
}

int RAM::getWordValue(uint16_t pos, uint16_t& val) const{

}

uint8_t* RAM::getByteAdress(uint16_t pos) const{
    return &memory_cells[pos];
}