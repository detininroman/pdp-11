#include "bit_array.hpp"

BitArray::BitArray(uint8_t const *const array, size_t size) {
    this->array = new uint8_t[size];
    memcpy(this->array, array, size);
    this->size_in_bytes = size;
}

BitArray::~BitArray() {
    delete array;
}

size_t BitArray::getSizeInBits() {
    return size_in_bytes * 8;
}

size_t BitArray::getSizeInBytes() {
    return size_in_bytes;
}

bool BitArray::getBit(int index) {
    if (index < 0 or index >= (int) getSizeInBits()) {
        throw std::runtime_error("Index of a bit out of array range.");
    }
    return array[index / 8] & (1 << index % 8);
}

uint8_t BitArray::getByte(int index) {
    if (index < 0 or index >= (int) getSizeInBytes()) {
        throw std::runtime_error("Index of a byte out of array range.");
    }
    return array[index];
}
