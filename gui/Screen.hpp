#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Screen : public GUIObject {
private:
    sf::Color darkGray = sf::Color(46, 46, 46);

public:

    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop) : GUIObject(window) {
        sf::Texture texture;
        texture.create(width, height);
        sprite_.setTexture(texture);
        sprite_.setPosition(xLeftTop, yLeftTop);
        sprite_.setColor(darkGray);
    }

    ~Screen() {};
};
