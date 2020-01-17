#pragma once

#include <SFML/Graphics.hpp>

#include "GUI_object.hpp"
#include "../emulator/params.hpp"


class Screen : public GUIObject {
protected:
    ScreenType type;

public:
    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int x_left_top, int y_left_top, ScreenType type);

    ~Screen() {}

    void draw();
};

Screen::Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int x_left_top, int y_left_top, ScreenType type) :
        GUIObject(window), type(type) {
    sf::Texture texture;
    texture.create(width, height);
    sprite.setTexture(texture);
    sprite.setPosition(x_left_top, y_left_top);
    sprite.setColor(gray);
}

void Screen::draw() {
    GUIObject::draw();
}

