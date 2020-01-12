#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"
#include "../emulator/params.hpp"


class Screen : public GUIObject {
private:
    sf::Color darkGray = sf::Color(46, 46, 46);
    // TODO: implement enum for screen types
    bool vRamScreen_ = false;

public:
    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop, bool vRamScreen);

    ~Screen() {};

    void draw();

    void draw(uint8_t *buff);
};

Screen::Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, bool vRamScreen = false) :
        GUIObject(window), vRamScreen_(vRamScreen) {
    sf::Texture texture;
    texture.create(width, height);
    sprite_.setTexture(texture);
    sprite_.setPosition(xLeftTop, yLeftTop);
    sprite_.setColor(darkGray);
}

void Screen::draw() {
    GUIObject::draw();
}

void Screen::draw(uint8_t *buff) {
    draw();
    if (vRamScreen_) {
        int multiplier = 4;
        int xSize = 128 * multiplier;
        int ySize = 64 * multiplier;

        sf::VertexArray arr(sf::Points, xSize * ySize);
        for (int i = 0; i < xSize; i++) {
            for (int j = 0; j < ySize; j++) {
                int rawIndex = j * xSize + i;
                int index = (j / multiplier) * xSize + (i / multiplier);
                uint8_t val = 255 - buff[index];

                arr[rawIndex] = sf::Vector2f(60 + 2 * i, 100 + 2 * j);
                arr[rawIndex].color = sf::Color(val, val, val);
            }
        }
        window_->draw(arr);
    }
}
