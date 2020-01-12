#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Button : public GUIObject {
private:
    sf::Font font_;
    sf::Text text_;
    sf::Color green = sf::Color(84, 185, 143);
    sf::Color darkGray = sf::Color(46, 46, 46);
    sf::Color lightGray = sf::Color(172, 172, 172);
    bool clicked;

public:
    sf::IntRect rect_;

    Button(sf::RenderWindow *window, sf::Font font, unsigned int width,
           unsigned int height, int xLeftTop, int yLeftTop,
           sf::String name, bool centered, int characterSize);

    ~Button() {};

    void draw();

    void clickHandler();

    void update();
};

Button::Button(sf::RenderWindow *window, sf::Font font,
               unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, sf::String name,
               bool centered = true, int characterSize = 36) :
        GUIObject(window), font_(font), clicked(false),
        rect_(sf::IntRect(xLeftTop, yLeftTop, width, height)) {

    sf::Texture texture;
    texture.create(width, height);
    sprite_.setTexture(texture);
    sprite_.setPosition(xLeftTop, yLeftTop);
    sprite_.setColor(darkGray);

    text_.setFont(font_);
    text_.setString(name);
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
}

void Button::clickHandler() {
    clicked = !clicked;
    std::cout << "Button " << text_.getString().toAnsiString() << std::endl;
}