#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"


class Screen : public GUIObject {

public:
    Screen(sf::RenderWindow *window) : GUIObject(window) {
        sf::Texture texture;
        texture.create(1400, 1100);
        sprite_.setTexture(texture);
        sprite_.setPosition(50, 50);
        sprite_.setColor(sf::Color(60, 63, 65));
    }

    ~Screen() {};
};
