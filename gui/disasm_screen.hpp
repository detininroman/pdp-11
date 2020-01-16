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

    void draw(const std::string &str);

};

DisAsmScreen::DisAsmScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                           int xLeftTop, int yLeftTop, ScreenType type) :
        Screen(window, width, height, xLeftTop, yLeftTop, type) {};

void DisAsmScreen::draw() {
    Screen::draw();
}

void DisAsmScreen::draw(const std::string &str) {
    draw();
    if (type_ != ScreenType::DISASM_SCREEN) {
        return;
    }
    if (str == "") {
        return;
    }
    std::cout << str << std::endl;
}
