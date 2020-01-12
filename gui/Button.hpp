#pragma once

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../emulator/params.hpp"
#include "../emulator/emulator.hpp"
#include "GUIObject.hpp"


std::unordered_map <ButtonType, sf::String> buttonNames = {
        {REG0,   "R0:"},
        {REG1,   "R1:"},
        {REG2,   "R2:"},
        {REG3,   "R3:"},
        {REG4,   "R4:"},
        {REG5,   "R5:"},
        {REG6,   "R6:"},
        {REG7,   "R7:"},
        {START,  "Start"},
        {STOP,   "Stop"},
        {STEP,   "Step"},
        {RUN,    "Run"},
        {N_FLAG, "N"},
        {Z_FLAG, "Z"},
        {V_FLAG, "V"},
        {C_FLAG, "C"},
        {SYNC,   "Sync"},
        {CONV,   "Conv"},
        {TICKS,  "Ticks:"},
};

class Button : public GUIObject {
private:
    sf::Font font_;
    sf::Text text_;
    sf::Color green = sf::Color(84, 185, 143);
    sf::Color darkGray = sf::Color(46, 46, 46);
    sf::Color lightGray = sf::Color(172, 172, 172);
    bool clicked;
    ButtonType type_;

public:
    sf::IntRect rect_;

    Button(sf::RenderWindow *window, sf::Font font, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop, ButtonType type, bool centered, int characterSize);

    ~Button() {};

    void draw();

    void clickHandler();

    void update();
};

Button::Button(sf::RenderWindow *window, sf::Font font, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, ButtonType type, bool centered = true, int characterSize = 36) :
        GUIObject(window), font_(font), clicked(false), type_(type),
        rect_(sf::IntRect(xLeftTop, yLeftTop, width, height)) {

    sf::Texture texture;
    texture.create(width, height);
    sprite_.setTexture(texture);
    sprite_.setPosition(xLeftTop, yLeftTop);
    sprite_.setColor(darkGray);

    text_.setFont(font_);
    text_.setString(buttonNames[type_]);
    text_.setCharacterSize(characterSize);
    text_.setFillColor(lightGray);

    float spriteWidth = sprite_.getLocalBounds().width;
    float spriteHeight = sprite_.getLocalBounds().height;
    float textWidth = text_.getLocalBounds().width;
    float textHeight = text_.getLocalBounds().height;

    auto shift = (centered) ? spriteWidth / 2 : textWidth / 2 + 20;
    text_.setPosition(xLeftTop + shift, yLeftTop + spriteHeight / 2);
    text_.setOrigin(textWidth / 2, textHeight / 2);
}

void Button::draw() {
    GUIObject::draw();
    window_->draw(text_);
}

void Button::update() {
    sprite_.setColor((clicked) ? green : darkGray);
    if (type_ >= REG0 && type_ <= REG7) {
        auto reg = Emulator::instance().getRegister((RegisterEnum) type_);
        text_.setString(buttonNames[type_] + " " + sf::String(std::to_string(reg)));
    }
}

void Button::clickHandler() {
    clicked = !clicked;
    std::cout << "Button " << text_.getString().toAnsiString() << std::endl;
}