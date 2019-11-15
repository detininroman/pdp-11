#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Button : public GUIObject {

public:
    sf::Font font_;
    sf::Text text_;

    Button(sf::RenderWindow *window, sf::Font font) : GUIObject(window), font_(font) {
        sf::Texture texture;
        texture.create(400, 100);
        sprite_.setTexture(texture);
        sprite_.setPosition(50, 1200);
        sprite_.setColor(sf::Color(60, 63, 65));

        text_.setFont(font_);
        text_.setString("Start");
        text_.setCharacterSize(48);
        text_.setFillColor(sf::Color::Red);

        float spriteWidth = sprite_.getLocalBounds().width;
        float spriteHeight = sprite_.getLocalBounds().height;
        float textWidth = text_.getLocalBounds().width;
        float textHeight = text_.getLocalBounds().height;

        text_.setPosition(50 + spriteWidth / 2, 1200 + spriteHeight / 2);
        text_.setOrigin(textWidth / 2, textHeight / 2);
    }

    ~Button() {};

    void draw() {
        window_->draw(sprite_);
        window_->draw(text_);
    }
};
