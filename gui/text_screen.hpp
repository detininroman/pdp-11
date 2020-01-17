#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "params.hpp"
#include "utils.hpp"
#include "../emulator/params.hpp"
#include "../misc/bit_array.hpp"


class TextScreen : public Screen {
private:
    sf::Text text;

public:
    TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height, int x_left_top,
               int y_left_top, ScreenType type, sf::Font &font, int character_size, int shift);

    void draw();

    void update();
};

TextScreen::TextScreen(sf::RenderWindow *window, unsigned int width, unsigned int height, int x_left_top,
                       int y_left_top, ScreenType type, sf::Font &font, int character_size = 36, int shift = 20) :
        Screen(window, width, height, x_left_top, y_left_top, type) {
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

void TextScreen::update() {
    std::string str;
    switch (type) {
        case ScreenType::DISASM_SCREEN:
            str = vec2str(Emulator::instance().getAssemblyCommands(33));
            break;
        case ScreenType::BYTECODE_SCREEN:
            str = vec2str(Emulator::instance().getByteCode(33));
            break;
        default:
            assert("wrong ScreenType");
            break;
    }
    text.setString(str);
}
