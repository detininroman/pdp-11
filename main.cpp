#include <SFML/Graphics.hpp>
#include <iostream>

//#include "emulator/emulator.hpp"
#include "gui/Screen.hpp"
#include "gui/Button.hpp"
#include "gui/GUIObject.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1350), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/font.ttf");

    Screen vRam(&window, 1050, 600, 50, 50, sf::Color(60, 63, 65));

    Screen byteCodeScreen(&window, 700, 600, 1150, 50, sf::Color(60, 63, 65));

    Screen disAsmScreen(&window, 700, 600, 1150, 700, sf::Color(60, 63, 65));

    Button emulateButton(&window, font, 400, 100, 700, 825,
                         "Emulate", sf::Color(60, 63, 65));
    Button stopButton(&window, font, 400, 100, 700, 950,
                      "Stop", sf::Color(60, 63, 65));
    Button stepButton(&window, font, 400, 100, 700, 1075,
                      "Step", sf::Color(60, 63, 65));
    Button startButton(&window, font, 400, 100, 700, 1200,
                       "Start", sf::Color(60, 63, 65));

    Button nFlag(&window, font, 70, 70, 700, 700, "N", sf::Color(60, 63, 65));
    Button zFlag(&window, font, 70, 70, 810, 700, "Z", sf::Color(60, 63, 65));
    Button vFlag(&window, font, 70, 70, 920, 700, "V", sf::Color(60, 63, 65));
    Button cFlag(&window, font, 70, 70, 1030, 700, "C", sf::Color(60, 63, 65));

//    Emulator::instance().initROM("emulator/rom.raw");

    auto buttons = {startButton, stopButton, stepButton,
                    emulateButton, nFlag, zFlag, vFlag, cFlag};

    auto screens = {vRam, byteCodeScreen, disAsmScreen};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                for (auto button : buttons) {
                    if (button.rect_.contains(position)) {
                        button.clickHandler();
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color(43, 43, 43));

        for (auto screen: screens) {
            screen.update();
        }
        for (auto button : buttons) {
            button.update();
        }

        for (auto screen: screens) {
            screen.draw();
        }
        for (auto button : buttons) {
            button.draw();
        }

        window.display();
    }
    return 0;
}
