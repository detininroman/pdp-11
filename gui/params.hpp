#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

sf::Color green = sf::Color(84, 185, 143);
sf::Color blue = sf::Color(62, 90, 124);
sf::Color lightGray = sf::Color(172, 172, 172);
sf::Color gray = sf::Color(46, 46, 46);
sf::Color darkGray = sf::Color(34, 34, 34);
sf::Color black = sf::Color::Black;

enum PDPState {
    INACTIVE,
    AUTO,
    MANUAL,
    FINISHED,
};

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
        {N_FLAG, "N:"},
        {Z_FLAG, "Z:"},
        {V_FLAG, "V:"},
        {C_FLAG, "C:"},
        {SYNC,   "Sync"},
        {CONV,   "Conv"},
        {TICKS,  "Ticks:"},
};