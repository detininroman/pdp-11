#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../emulator/params.hpp"
#include "../emulator/emulator.hpp"
#include "params.hpp"
#include "GUI_object.hpp"


class Button : public GUIObject {
private:
    sf::Font font_;
    sf::Text text_;
    bool clicked;
    ButtonType type_;

public:
    sf::IntRect rect_;

    Button(sf::RenderWindow *window, sf::Font font, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop, ButtonType type, int characterSize);

    ~Button() {};

    void draw();

    void clickHandler();

    void update();
};

Button::Button(sf::RenderWindow *window, sf::Font font, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, ButtonType type, int characterSize = 36) :
        GUIObject(window), font_(font), clicked(false), type_(type),
        rect_(sf::IntRect(xLeftTop, yLeftTop, width, height)) {

    sf::Texture texture;
    texture.create(width, height);
    sprite_.setTexture(texture);
    sprite_.setPosition(xLeftTop, yLeftTop);
    sprite_.setColor(gray);

    text_.setFont(font_);
    text_.setString(buttonNames[type_]);
    text_.setCharacterSize(characterSize);
    text_.setFillColor(lightGray);

    float spriteWidth = sprite_.getLocalBounds().width;
    float spriteHeight = sprite_.getLocalBounds().height;
    float textWidth = text_.getLocalBounds().width;
    float textHeight = text_.getLocalBounds().height;

    bool leftAligned = (type_ >= REG0 && type_ <= REG7) || type_ == TICKS || (type_ >= N_FLAG && type_ <= C_FLAG);
    auto centered = !leftAligned;
    auto shift = (centered) ? spriteWidth / 2 : textWidth / 2 + 20;
    text_.setPosition(xLeftTop + shift, yLeftTop + spriteHeight / 2);
    text_.setOrigin(textWidth / 2, textHeight / 2);
}

void Button::draw() {
    GUIObject::draw();
    window_->draw(text_);
}

void Button::update() {
    sprite_.setColor((clicked) ? green : gray);
    text_.setFillColor((clicked) ? black : lightGray);

    std::string val;
    if (type_ >= ButtonType::REG0 && type_ <= ButtonType::REG7) {
        val = std::to_string(Emulator::instance().getRegister((RegisterEnum) type_));
    } else if (type_ == ButtonType::TICKS) {
        val = std::to_string(Emulator::instance().getTicks());
    } else if (type_ >= ButtonType::N_FLAG && type_ <= ButtonType::C_FLAG) {
        ProcessorStatusWordEnum flag_name;
        switch (type_) {
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
    text_.setString(buttonNames[type_] + " " + sf::String(val));
}

void Button::clickHandler() {
    clicked = !clicked;
    std::cout << "Button " << text_.getString().toAnsiString() << std::endl;
}