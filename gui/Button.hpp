#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Button : public GUIObject {

public:
    sf::Font font_;
    sf::Text text_;
    sf::Color color_ = sf::Color(60, 63, 65);
    bool clicked;
    sf::IntRect rect_;

    Button(sf::RenderWindow *window, sf::Font font,
           unsigned int width, unsigned int height, int xLeftTop, int yLeftTop,
           sf::String name, bool centered = true, int characterSize = 42) :
            GUIObject(window), font_(font), clicked(false),
            rect_(sf::IntRect(xLeftTop, yLeftTop, width, height)) {

        sf::Texture texture;
        texture.create(width, height);
        sprite_.setTexture(texture);
        sprite_.setPosition(xLeftTop, yLeftTop);
        sprite_.setColor(color_);

        text_.setFont(font_);
        text_.setString(name);
        text_.setCharacterSize(characterSize);
        text_.setFillColor(sf::Color::Yellow);

        float spriteWidth = sprite_.getLocalBounds().width;
        float spriteHeight = sprite_.getLocalBounds().height;
        float textWidth = text_.getLocalBounds().width;
        float textHeight = text_.getLocalBounds().height;

        auto shift = (centered) ? spriteWidth / 2 : textWidth / 2 + 20;
        text_.setPosition(xLeftTop + shift, yLeftTop + spriteHeight / 2);
        text_.setOrigin(textWidth / 2, textHeight / 2);
    }

    ~Button() {};

    void draw() {
        window_->draw(sprite_);
        window_->draw(text_);
    }

    void clickHandler() {
        clicked = !clicked;
        std::cout << "Button " << text_.getString().toAnsiString() << std::endl;
    }

    void update() {
        text_.setFillColor((clicked) ? sf::Color::Green : sf::Color::Red);
    }
};
