#pragma once

#include <cstdint>
#include <functional>

struct instrPackage {
    uint8_t **regs8;
    uint8_t *source8;
    uint8_t *dest8;

    uint16_t **regs16;
    uint16_t *source16;
    uint16_t *dest16;

};

enum OPERAND_TYPE {
    MEM8,  // byte addressing
    MEM16, // word addressing
    CONST,
    NOP
};

struct commandDecomposed {
		// double call
    commandDecomposed(/*std::function<bool(instrPackage)> f, */int n, int t) : /*func(f), */nOps(n), nTicks(t) {}

    //std::function<bool(instrPackage)> func;
    int nOps;
    int nTicks;
};

/*bool mov_(instrPackage data) {
    *data.dest8 = *data.source8;
    *data.dest16 = *data.source16;
    return true;
}*/

