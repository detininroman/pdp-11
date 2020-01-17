#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

sf::Color green = sf::Color(84, 185, 143);
sf::Color blue = sf::Color(62, 90, 124);
sf::Color light_gray = sf::Color(172, 172, 172);
sf::Color gray = sf::Color(46, 46, 46);
sf::Color dark_gray = sf::Color(34, 34, 34);
sf::Color black = sf::Color::Black;

enum PDPState {
    INACTIVE,
    EXECUTE,
    AUTO,
    MANUAL,
    STOPPED,
    FINISHED,
};

std::unordered_map <PDPState, std::string> states_map = {
        {INACTIVE, "inactive"},
        {AUTO,     "auto"},
        {MANUAL,   "manual"},
        {STOPPED,  "stopped"},
        {FINISHED, "finished"},
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
    EXEC,
    STEP,
    STOP,
    START,
    N_FLAG,
    Z_FLAG,
    V_FLAG,
    C_FLAG,
    SYNC,
    CONV,
    TICKS_PIPE,
    TICKS_NO_PIPE,
    RESET,
};

std::unordered_map <ButtonType, sf::String> button_names = {
        {REG0,          "R0:"},
        {REG1,          "R1:"},
        {REG2,          "R2:"},
        {REG3,          "R3:"},
        {REG4,          "R4:"},
        {REG5,          "R5:"},
        {REG6,          "R6:"},
        {REG7,          "R7:"},
        {START,         "Start"},
        {STOP,          "Stop"},
        {STEP,          "Step"},
        {EXEC,          "Execute"},
        {N_FLAG,        "N:"},
        {Z_FLAG,        "Z:"},
        {V_FLAG,        "V:"},
        {C_FLAG,        "C:"},
        {SYNC,          "Sync"},
        {CONV,          "Conv"},
        {TICKS_PIPE,    "Ticks:"},
        {TICKS_NO_PIPE, "Ticks:"},
        {RESET,         "Reset"},
};