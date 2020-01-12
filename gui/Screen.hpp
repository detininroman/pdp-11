#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Screen : public GUIObject {
private:
    sf::Color color_ = sf::Color(60, 63, 65);

public:

    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop) : GUIObject(window) {
        sf::Texture texture;
        texture.create(width, height);
        sprite_.setTexture(texture);
        sprite_.setPosition(xLeftTop, yLeftTop);
        sprite_.setColor(color_);
    }

    ~Screen() {};
};
