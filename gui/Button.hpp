#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Button : public GUIObject {

public:
    sf::Font font_;
    sf::Text text_;
    sf::IntRect rect_;

    Button(sf::RenderWindow *window, sf::Font font,
           unsigned int width, unsigned int height, int xLeftTop, int yLeftTop,
           sf::String name, sf::Color color) :
            GUIObject(window), font_(font),
            rect_(sf::IntRect(xLeftTop, yLeftTop, width, height)) {

        sf::Texture texture;
        texture.create(width, height);
        sprite_.setTexture(texture);
        sprite_.setPosition(xLeftTop, yLeftTop);
        sprite_.setColor(color);

        text_.setFont(font_);
        text_.setString(name);
        text_.setCharacterSize(48);
        text_.setFillColor(sf::Color::Red);

        float spriteWidth = sprite_.getLocalBounds().width;
        float spriteHeight = sprite_.getLocalBounds().height;
        float textWidth = text_.getLocalBounds().width;
        float textHeight = text_.getLocalBounds().height;

        text_.setPosition(xLeftTop + spriteWidth / 2,
                          yLeftTop + spriteHeight / 2);
        text_.setOrigin(textWidth / 2, textHeight / 2);
    }

    ~Button() {};

    void draw() {
        window_->draw(sprite_);
        window_->draw(text_);
    }

    void clickHandler() {
        std::cout << "Button " << text_.getString().toAnsiString() << std::endl;
    }

    void update() {

    }
};
