#pragma once

#include <SFML/Graphics.hpp>


class GUIObject {
protected:
    sf::RenderWindow *window_;
    sf::Sprite sprite_;

public:

    GUIObject(sf::RenderWindow *window);

    virtual ~GUIObject() {};

    virtual void draw();

    virtual void update();
};

GUIObject::GUIObject(sf::RenderWindow *window) : window_(window) {}

void GUIObject::draw() {
    window_->draw(sprite_);
}

void GUIObject::update() {
}
