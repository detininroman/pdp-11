#include "instructions.hpp"


void mov(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    *operand2 = *operand1;

    registers->psw.N = (*operand2) & (1 << 15);
    registers->psw.Z = (*operand2 == 0);
    registers->psw.V = false;
}

void sob(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {
    (*operand1)--;
    registers->pc -= 2 * *operand2;
    // To compensate PC += 2 in the end of emulation step.
    registers->pc -= 2;
}

void halt(struct Registers *registers, uint16_t *operand1, uint16_t *operand2) {

}