#pragma once

#include <SFML/Graphics.hpp>


class GUIObject {

public:
    sf::RenderWindow *window_;
    sf::Sprite sprite_;

    GUIObject(sf::RenderWindow *window) : window_(window) {};

    virtual ~GUIObject() {};

    virtual void draw() {
        window_->draw(sprite_);
    }

    virtual void update() {}
};
