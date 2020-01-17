#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "../emulator/params.hpp"


class VRamScreen : public Screen {
private:
    int x_size;
    int y_size;
    int multiplier;
    sf::VertexArray arr;

public:
    VRamScreen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int x_left_top, int y_left_top, ScreenType type, int x_size, int y_size, int multiplier);

    void draw();

    void update(uint8_t *buff);
};

VRamScreen::VRamScreen(sf::RenderWindow *window, unsigned int width, unsigned int height, int x_left_top,
                       int y_left_top, ScreenType type, int x_size = 128, int y_size = 64, int multiplier = 8) :
        Screen(window, width, height, x_left_top, y_left_top, type),
        x_size(x_size), y_size(y_size), multiplier(multiplier),
        arr(sf::VertexArray(sf::Points, x_size * y_size * multiplier * multiplier)) {}

void VRamScreen::draw() {
    Screen::draw();
    window->draw(arr);
};

void VRamScreen::update(uint8_t *buff) {
    int index = 0;
    for (int x = 0; x < x_size; x++) {
        for (int y = 0; y < y_size; y++) {
            uint8_t val = buff[y * x_size + x];
            for (int i = 0; i < multiplier * multiplier; i++) {
                arr[index] = sf::Vector2f(60 + multiplier * x + i % multiplier, 100 + multiplier * y + i / multiplier);
                arr[index].color = sf::Color(val, val, val);
                index += 1;
            }
        }
    }

}
