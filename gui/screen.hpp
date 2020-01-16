#pragma once

#include <SFML/Graphics.hpp>
#include "GUI_object.hpp"
#include "../emulator/params.hpp"


class Screen : public GUIObject {
protected:
    ScreenType type_;

public:
    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop, ScreenType type);

    ~Screen() {};

    void draw();
};

Screen::Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, ScreenType type) :
        GUIObject(window), type_(type) {
    sf::Texture texture;
    texture.create(width, height);
    sprite_.setTexture(texture);
    sprite_.setPosition(xLeftTop, yLeftTop);
    sprite_.setColor(gray);
}

void Screen::draw() {
    GUIObject::draw();
}

