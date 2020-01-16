#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "../emulator/params.hpp"


class TextScreen : public Screen {
private:
    sf::Font font_;
    sf::Text text_;

public:
    TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, ScreenType type, sf::Font font, int characterSize);

    void draw();

    void draw(const std::string &str);
};

TextScreen::TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                       int xLeftTop, int yLeftTop, ScreenType type, sf::Font font, int characterSize = 36) :
        Screen(window, width, height, xLeftTop, yLeftTop, type), font_(font) {
    text_.setFont(font_);
    text_.setString("some text");
    text_.setCharacterSize(characterSize);
    text_.setFillColor(lightGray);
    text_.setPosition(xLeftTop + 20, yLeftTop + 20);
}

void TextScreen::draw() {
    Screen::draw();
}

void TextScreen::draw(const std::string &str) {
    draw();
    text_.setString(str);
    window_->draw(text_);
}
