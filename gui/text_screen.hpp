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
               int x_left_top, int y_left_top, ScreenType type, sf::Font font, int character_size);

    void draw();

    void update(const std::string &str);
};

TextScreen::TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                       int x_left_top, int y_left_top, ScreenType type, sf::Font font, int character_size = 36) :
        Screen(window, width, height, x_left_top, y_left_top, type), font_(font) {
    text_.setFont(font_);
    text_.setString("some text");
    text_.setCharacterSize(character_size);
    text_.setFillColor(lightGray);
    text_.setPosition(x_left_top + 20, y_left_top + 20);
}

void TextScreen::draw() {
    Screen::draw();
    window_->draw(text_);
}

void TextScreen::update(const std::string &str) {
    text_.setString(str);
}
