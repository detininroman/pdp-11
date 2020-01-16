#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.hpp"
#include "../emulator/params.hpp"


class VRamScreen : public Screen {
private:
    void draw();


public:
    VRamScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, ScreenType type);

    void draw(uint8_t *buff);

};

VRamScreen::VRamScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
                       int xLeftTop, int yLeftTop, ScreenType type) :
        Screen(window, width, height, xLeftTop, yLeftTop, type) {};

void VRamScreen::draw() {
    Screen::draw();
};

void VRamScreen::draw(uint8_t *buff) {
    draw();
    if (type_ != ScreenType::VRAM_SCREEN) {
        return;
    }

    int multiplier = 8;
    int xSize = 128;
    int ySize = 64;

    sf::VertexArray arr(sf::Points, xSize * ySize * multiplier * multiplier);
    int index = 0;
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            uint8_t val = buff[y * xSize + x];
            for (int i = 0; i < multiplier * multiplier; i++) {
                arr[index] = sf::Vector2f(60 + multiplier * x + i % multiplier,
                                          100 + multiplier * y + i / multiplier);
                arr[index].color = sf::Color(val, val, val);
                index += 1;
            }
        }
    }
    window_->draw(arr);
}
