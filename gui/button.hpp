#pragma once

#include <SFML/Graphics.hpp>
#include "../emulator/params.hpp"
#include "../emulator/emulator.hpp"
#include "params.hpp"
#include "GUI_object.hpp"
#include <cassert>
#include <iostream>

class Button : public GUIObject {
private:
    sf::Text text;
    bool clicked;
    ButtonType type;
    bool disabled_button;

public:
    sf::IntRect rect;

    Button(sf::RenderWindow *window, sf::Font &font, unsigned int width, unsigned int height,
           int x_left_top, int y_left_top, ButtonType type, int character_size);

    ~Button() {};

    void draw();

    void clickHandler();

    void update();
};

Button::Button(sf::RenderWindow *window, sf::Font &font, unsigned int width, unsigned int height,
               int x_left_top, int y_left_top, ButtonType type, int character_size = 36) :
        GUIObject(window), clicked(false), type(type),
        rect(sf::IntRect(x_left_top, y_left_top, width, height)) {
    disabled_button = (type >= REG0 && type <= REG7) || (type >= N_FLAG && type <= C_FLAG) ||
                      type == TICKS_PIPE || type == TICKS_NO_PIPE;

    sf::Texture texture;
    texture.create(width, height);
    sprite.setTexture(texture);
    sprite.setPosition(x_left_top, y_left_top);
    sprite.setColor((disabled_button) ? gray : blue);

    text.setFont(font);
    text.setString(button_names[type]);
    text.setCharacterSize(character_size);
    text.setFillColor((disabled_button) ? light_gray : black);

    float spriteWidth = sprite.getLocalBounds().width;
    float spriteHeight = sprite.getLocalBounds().height;
    float textWidth = text.getLocalBounds().width;
    float textHeight = text.getLocalBounds().height;

    auto centered = !disabled_button;
    auto shift = (centered) ? spriteWidth / 2 : textWidth / 2 + 20;
    text.setPosition(x_left_top + shift, y_left_top + spriteHeight / 2);
    text.setOrigin(textWidth / 2, textHeight / 2);
}

void Button::draw() {
    GUIObject::draw();
    window->draw(text);
}

void Button::update() {
    if (!disabled_button) {
        sprite.setColor((clicked) ? green : blue);
    }

    std::string val;
    if (type >= ButtonType::REG0 && type <= ButtonType::REG7) {
        val = std::to_string(Emulator::instance().getRegister((RegisterEnum) type));
    } else if (type == ButtonType::TICKS_PIPE) {
        val = std::to_string(Emulator::instance().getTicksPipe());
    } else if (type == ButtonType::TICKS_NO_PIPE) {
        val = std::to_string(Emulator::instance().getTicksNoPipe());
    } else if (type >= ButtonType::N_FLAG && type <= ButtonType::C_FLAG) {
        ProcessorStatusWordEnum flag_name;
        switch (type) {
            case ButtonType::N_FLAG:
                flag_name = PSW_N;
                break;
            case ButtonType::Z_FLAG:
                flag_name = PSW_Z;
                break;
            case ButtonType::V_FLAG:
                flag_name = PSW_V;
                break;
            case ButtonType::C_FLAG:
                flag_name = PSW_C;
                break;
            default:
                assert(0);
        }
        val = std::to_string(Emulator::instance().getProcessorStatusWord(flag_name));
    }
    text.setString(button_names[type] + " " + sf::String(val));
}

void Button::clickHandler() {
    clicked = !clicked;
    std::cout << "Button " << text.getString().toAnsiString() << std::endl;
}