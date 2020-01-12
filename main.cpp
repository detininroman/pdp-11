#include <SFML/Graphics.hpp>
#include <iostream>

//#include "emulator/emulator.hpp"
#include "gui/Screen.hpp"
#include "gui/Button.hpp"
#include "gui/GUIObject.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1400), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/font.ttf");

    Screen screen(&window, 1000, 800, 50, 50, sf::Color(60, 63, 65));

    Button emulateButton(&window, font, 400, 100, 550, 875,
                         "Emulate", sf::Color(60, 63, 65));
    Button stopButton(&window, font, 400, 100, 550, 1000,
                      "Stop", sf::Color(60, 63, 65));
    Button stepButton(&window, font, 400, 100, 550, 1125,
                      "Step", sf::Color(60, 63, 65));
    Button startButton(&window, font, 400, 100, 550, 1250,
                       "Start", sf::Color(60, 63, 65));
//    Emulator::instance().initROM("emulator/rom.raw");

    auto buttons = {startButton, stopButton, stepButton,
                    emulateButton};

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

        screen.update();
        for (auto button : buttons) {
            button.update();
        }

        screen.draw();
        for (auto button : buttons) {
            button.draw();
        }

        window.display();
    }
    return 0;
}
