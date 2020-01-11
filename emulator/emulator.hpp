#pragma once

#include "memory/memory.hpp"
#include "instructions/instructions.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <memory>


class Emulator {
public:
    Emulator() = default;

    static uint8_t getVideo();

    bool initROM(std::string fileName);

    void startAll();

    static void step();

    static Emulator &instance();

private:
    ~Emulator();

    Emulator(Emulator const &emulator) = delete;

    Emulator &operator=(Emulator const &emulator) = delete;

    typedef enum {
        FETCH,
        DECODE,
        LOAD_OPERAND,
        EXCECUTE,
        STORE_RES
    } PIPELINE_STAGE;

    int ticks;
    // TODO:: move to another class, change according to real data
    const int defaultTicksAddCount = 50;

    PIPELINE_STAGE currentStage;

    Memory memory;

    uint16_t fetched_bytes;
    struct Instruction *current_instr;


    const std::vector<struct Instruction> instructionTable =
            {
                    {0xf000, 0x1000, "mov",  mov},
/*                  {0xf000, 0x9000, "movb", movb},
                    {0xf000, 0x2000, "cmp",  cmp},
                    {0xf000, 0xa000, "cmpb", cmpb},
                    {0xf000, 0x3000, "bit",  bit},
                    {0xf000, 0xb000, "bitb", bitb},
                    {0xf000, 0x4000, "bic",  bic},
                    {0xf000, 0xc000, "bicb", bicb},
                    {0xf000, 0x5000, "bis",  bis},
                    {0xf000, 0xd000, "bisb", bisb},
                    {0xf000, 0x6000, "add",  add},
                    {0xf000, 0xe000, "sub",  sub},
                    {0xfe00, 0x7000, "mul",  mul},
                    {0xfe00, 0x7200, "div",  div},
                    {0xfe00, 0x7400, "ash",  ash},
                    {0xfe00, 0x7600, "ashc", ashc},
                    {0xfe00, 0x7800, "xor",  xor_},
*/
                    {0xfe00, 0x7e00, "sob",  sob},
/*                  {0xffc0, 0x00c0, "swab", swab},
                    {0xffc0, 0x0a00, "clr",  clr},
                    {0xffc0, 0x8a00, "clrb", clrb},
                    {0xffc0, 0x0a40, "com",  com},
                    {0xffc0, 0x8a40, "comb", comb},
                    {0xffc0, 0x0a80, "inc",  inc},
                    {0xffc0, 0x8a80, "incb", incb},
                    {0xffc0, 0x0ac0, "dec",  dec},
                    {0xffc0, 0x8ac0, "decb", decb},
                    {0xffc0, 0x0b00, "neg",  neg},
                    {0xffc0, 0x8b00, "negb", negb},
                    {0xffc0, 0x0b40, "adc",  adc},
                    {0xffc0, 0x8b40, "adcb", adcb},
                    {0xffc0, 0x0b80, "sbc",  sbc},
                    {0xffc0, 0x8b80, "sbcb", sbcb},
                    {0xffc0, 0x0bc0, "tst",  tst},
                    {0xffc0, 0x8bc0, "tstb", tstb},
                    {0xffc0, 0x0c00, "ror",  ror},
                    {0xffc0, 0x8c00, "rorb", rorb},
                    {0xffc0, 0x0c40, "rol",  rol},
                    {0xffc0, 0x8c40, "rolb", rolb},
                    {0xffc0, 0x0c80, "asr",  asr},
                    {0xffc0, 0x8c80, "asrb", asrb},
                    {0xffc0, 0x0cc0, "asl",  asl},
                    {0xffc0, 0x8cc0, "aslb", aslb},
                    {0xffc0, 0x0d00, "mark", mark},
                    {0xffc0, 0x8d00, "mtps", mtps},
                    {0xffc0, 0x0d40, "mfpi", mfpi},
                    {0xffc0, 0x8d40, "mfpd", mfpd},
                    {0xffc0, 0x0d80, "mtpi", mtpi},
                    {0xffc0, 0x8d80, "mtpd", mtpd},
                    {0xffc0, 0x0dc0, "sxt",  sxt},
                    {0xffc0, 0x8dc0, "mfps", mfps},
*/
                    {0xffc0, 0x0000, "halt", halt},
            };

    void fetch();

    void decode();

    void loadOperand();

    void execute();

    void storeRes();

    void initTable();
};