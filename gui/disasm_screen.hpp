#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "../emulator/params.hpp"


class DisAsmScreen : public Screen {
private:
    sf::Text commands;

    void draw();

public:
    DisAsmScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                 int xLeftTop, int yLeftTop, ScreenType type);

    void draw(const std::vector <std::string> &commands);

};

DisAsmScreen::DisAsmScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                           int xLeftTop, int yLeftTop, ScreenType type) :
        Screen(window, width, height, xLeftTop, yLeftTop, type) {};

void DisAsmScreen::draw() {
    Screen::draw();
}

void DisAsmScreen::draw(const std::vector <std::string> &commands) {
    draw();
    if (type_ != ScreenType::DISASM_SCREEN) {
        return;
    }
    if (commands.empty()) {
        return;
    }
    for (auto cmd : commands) {
        std::cout << cmd << std::endl;
    }
    std::cout << "_________" << std::endl;
}
