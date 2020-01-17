#pragma once

#include <SFML/Graphics.hpp>


class GUIObject {
protected:
    sf::RenderWindow *window;
    sf::Sprite sprite;

public:

    GUIObject(sf::RenderWindow *window);

    virtual ~GUIObject() {};

    virtual void draw();

    void update();
};

GUIObject::GUIObject(sf::RenderWindow *window) : window(window) {};

void GUIObject::draw() {
    window->draw(sprite);
}

void GUIObject::update() {
}
