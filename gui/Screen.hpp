#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Screen : public GUIObject {

public:
    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop, sf::Color color) : GUIObject(window) {
        sf::Texture texture;
        texture.create(width, height);
        sprite_.setTexture(texture);
        sprite_.setPosition(xLeftTop, yLeftTop);
        sprite_.setColor(color);
    }

    ~Screen() {};
};
