#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "../emulator/params.hpp"


class DisAsmScreen : public Screen {
private:
    sf::Font font_;
    sf::Text text_;

    void draw();

public:
    DisAsmScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                 int xLeftTop, int yLeftTop, ScreenType type, sf::Font font, int characterSize);

    void draw(const std::vector <std::string> &commands);

};

DisAsmScreen::DisAsmScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                           int xLeftTop, int yLeftTop, ScreenType type, sf::Font font, int characterSize = 36) :
        Screen(window, width, height, xLeftTop, yLeftTop, type), font_(font) {
    text_.setFont(font_);
    text_.setString("asm commands should be here");
    text_.setCharacterSize(characterSize);
    text_.setFillColor(lightGray);
    text_.setPosition(xLeftTop + 20, yLeftTop + 20);
};

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

    std::string text;
    for (auto cmd : commands) {
        text += cmd + "\n";
    }
//    std::cout << text + "\n_________" << std::endl;
    text_.setString(text);
    window_->draw(text_);
}
