#pragma once

#include <SFML/Graphics.hpp>
#include "GUIObject.hpp"
#include "../emulator/params.hpp"


class Screen : public GUIObject {
private:
    sf::Color darkGray = sf::Color(46, 46, 46);
    ScreenType type_;

public:
    Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
           int xLeftTop, int yLeftTop, ScreenType type);

    ~Screen() {};

    void draw();

    void draw(uint8_t *buff);

    void draw(const std::string &str);
};

Screen::Screen(sf::RenderWindow *window, unsigned int width, unsigned int height,
               int xLeftTop, int yLeftTop, ScreenType type) :
        GUIObject(window), type_(type) {
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

void Screen::draw(const std::string &str) {
    draw();
    if (type_ != ScreenType::DISASM_SCREEN) {
        return;
    }
    if (str == "") {
        return;
    }
    std::cout << str << std::endl;
}
