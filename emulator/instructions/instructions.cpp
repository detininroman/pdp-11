#include "instructions.hpp"
#include "../params.hpp"

Error mov(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    *operand2 = *operand1;

    registers->psw.N = (*operand2) & (1 << 15);
    registers->psw.Z = (*operand2 == 0);
    registers->psw.V = false;

    return Error::OK;
}

Error cmp(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    uint32_t res = *operand1 - *operand2;

    registers->psw.N = res & (1 << 16);
    registers->psw.Z = (res == 0);
    registers->psw.C = ((res & (1 << 16)) != 0);
    registers->psw.V = ((*operand1 & (1 << 15)) != (*operand2 & (1 << 15))) &&
                       ((*operand2 & (1 << 15)) == (res & (1 << 15)));

    return Error::OK;
}

Error add(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    uint32_t res = *operand2 + *operand1;
    *operand2 = res;

    registers->psw.C = ((res & (1 << 16)) != 0);
    registers->psw.N = ((res & (1 << 15)) != 0);
    registers->psw.Z = (res == 0);
    registers->psw.V = ((*operand1 & (1 << 15)) == (*operand2 & (1 << 15))) &&
                       ((*operand1 & (1 << 15)) != (res & (1 << 15)));

    return Error::OK;
}

Error sub(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    uint32_t res = *operand2 - *operand1;
    *operand2 = res;

    registers->psw.C = ((res & (1 << 16)) != 0);
    registers->psw.N = ((res & (1 << 15)) != 0);
    registers->psw.Z = (res == 0);
    registers->psw.V = ((*operand1 & (1 << 15)) != (*operand2 & (1 << 15))) &&
                       ((*operand1 & (1 << 15)) == (res & (1 << 15)));

    return Error::OK;
}

// MUL R, src -> (R,R+1) = R × src
// If R is odd, the high 16 bits of the result should not be stored
Error mul(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    uint32_t res = (*operand1) * (*operand2);
    *operand1 = uint16_t(res >> 16);
    *(operand1 + 1) = uint16_t(res);

    registers->psw.N = res & (1 << 15);
    registers->psw.Z = (res == 0);
    registers->psw.V = false;
    registers->psw.C =
            (((res & 0xFFFF0000) != 0) && ((res & (1U << 31)) == 0)) ||
            (((res & 0xFFFF0000) != 0xFFFF0000) &&
             ((res & (1U << 31)) == (1U << 31)));

    return Error::OK;
}

Error div(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    registers->psw.C = (*operand2 == 0);
    if (*operand2 == 0) {
        registers->psw.V = true;
        return Error::DIVISION_BY_ZERO;
    }

    uint32_t dividend = (*operand1 << 16) + *(operand1 + 1);
    uint16_t quotient = dividend / *operand2;
    uint32_t big_quotient = dividend / *operand2;
    uint16_t remainder = dividend - quotient * *operand2;
    if (big_quotient > (uint32_t) (quotient & 0x7FFF)) {
        // Quotient exceeds 15 bits
        registers->psw.V = true;
        return Error::OVERFLOW;
    }

    *operand1 = quotient;
    *(operand1 + 1) = remainder;

    registers->psw.N = ((quotient & (1 << 15)) != 0);
    registers->psw.Z = (quotient == 0);

    return Error::OK;
}

Error xor_(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    *operand2 ^= *operand1;

    registers->psw.N = ((*operand2 & (1 << 15)) != 0);
    registers->psw.Z = (*operand2 == 0);
    registers->psw.V = false;

    return Error::OK;
}

Error sob(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    (*operand1)--;
    registers->pc -= 2 * *operand2;
    // To compensate PC += 2 in the end of emulation step.
    registers->pc -= 2;

    return Error::OK;
}

Error clr(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    *operand1 = 0;

    registers->psw.N = false;
    registers->psw.Z = true;
    registers->psw.V = false;
    registers->psw.C = false;

    return Error::OK;
}

Error inc(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    (*operand1)++;

    registers->psw.N = ((*operand1 & (1 << 15)) != 0);
    registers->psw.Z = (*operand1 == 0);
    registers->psw.V = (*operand1 - 1 == 0x7fff);

    return Error::OK;
}

Error dec(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    (*operand1)--;

    registers->psw.N = ((*operand1 & (1 << 15)) != 0);
    registers->psw.Z = (*operand1 == 0);
    registers->psw.V = (*operand1 + 1 == 0x8000);

    return Error::OK;
}

Error halt(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    registers->pc = RAM_SIZE + VIDEO_SIZE + ROM_SIZE;
    return Error::OK;
}

