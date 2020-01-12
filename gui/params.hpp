#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

enum ScreenType {
    VRAM_SCREEN,
    BYTECODE_SCREEN,
    DISASM_SCREEN,
};

enum ButtonType {
    REG0,
    REG1,
    REG2,
    REG3,
    REG4,
    REG5,
    REG6,
    REG7,
    RUN,
    STEP,
    STOP,
    START,
    N_FLAG,
    Z_FLAG,
    V_FLAG,
    C_FLAG,
    SYNC,
    CONV,
    TICKS,
};

std::unordered_map <ButtonType, sf::String> buttonNames = {
        {REG0,   "R0:"},
        {REG1,   "R1:"},
        {REG2,   "R2:"},
        {REG3,   "R3:"},
        {REG4,   "R4:"},
        {REG5,   "R5:"},
        {REG6,   "R6:"},
        {REG7,   "R7:"},
        {START,  "Start"},
        {STOP,   "Stop"},
        {STEP,   "Step"},
        {RUN,    "Run"},
        {N_FLAG, "N"},
        {Z_FLAG, "Z"},
        {V_FLAG, "V"},
        {C_FLAG, "C"},
        {SYNC,   "Sync"},
        {CONV,   "Conv"},
        {TICKS,  "Ticks:"},
};