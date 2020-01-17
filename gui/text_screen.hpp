#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "../emulator/params.hpp"


class TextScreen : public Screen {
private:
    sf::Font font;
    sf::Text text;

public:
    TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height, int x_left_top,
               int y_left_top, ScreenType type, sf::Font font, int character_size, int shift);

    void draw();

    void update(const std::string &str);
};

TextScreen::TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height, int x_left_top,
                       int y_left_top, ScreenType type, sf::Font font, int character_size = 36, int shift = 20) :
        Screen(window, width, height, x_left_top, y_left_top, type), font(font) {
    text.setFont(font);
    text.setString("some text");
    text.setCharacterSize(character_size);
    text.setFillColor(light_gray);
    text.setPosition(x_left_top + shift, y_left_top + shift);
}

void TextScreen::draw() {
    Screen::draw();
    window->draw(text);
}

void TextScreen::update(const std::string &str) {
    text.setString(str);
}
