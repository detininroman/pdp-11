#pragma once

class BitArray {
public:
    BitArray(uint8_t const *const array, size_t size);

    ~BitArray();

    size_t getSizeInBits();

    size_t getSizeInBytes();

    bool getBit(int index);

    uint8_t getByte(int index);

private:
    uint8_t *array;
    size_t size_in_bytes;
};