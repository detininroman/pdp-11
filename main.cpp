#include <SFML/Graphics.hpp>
#include <iostream>

#include "emulator/emulator.hpp"
#include "emulator/params.hpp"
#include "gui/Screen.hpp"
#include "gui/Button.hpp"
#include "gui/GUIObject.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1350), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/helvetica.ttf");

    Screen vRam(&window, 1050, 600, 50, 50, true);
    Screen byteCodeScreen(&window, 700, 600, 1150, 50);
    Screen disAsmScreen(&window, 700, 600, 1150, 700);

    Button runButton(&window, font, 310, 70, 450, 1150, "Run");
    Button stopButton(&window, font, 310, 70, 450, 1225, "Stop");
    Button stepButton(&window, font, 310, 70, 790, 1150, "Step");
    Button startButton(&window, font, 310, 70, 790, 1225, "Start");

    Button nFlag(&window, font, 70, 70, 450, 775, "N");
    Button zFlag(&window, font, 70, 70, 530, 775, "Z");
    Button vFlag(&window, font, 70, 70, 610, 775, "V");
    Button cFlag(&window, font, 70, 70, 690, 775, "C");

    Button R0(&window, font, 350, 70, 50, 700, "R0:", false);
    Button R1(&window, font, 350, 70, 50, 775, "R1:", false);
    Button R2(&window, font, 350, 70, 50, 850, "R2:", false);
    Button R3(&window, font, 350, 70, 50, 925, "R3:", false);
    Button R4(&window, font, 350, 70, 50, 1000, "R4:", false);
    Button R5(&window, font, 350, 70, 50, 1075, "R5:", false);
    Button R6(&window, font, 350, 70, 50, 1150, "R6:", false);
    Button R7(&window, font, 350, 70, 50, 1225, "R7:", false);

    Button syncButton(&window, font, 310, 70, 450, 700, "Sync");
    Button conveyorButton(&window, font, 310, 70, 790, 700, "Conv");
    Button ticksButton(&window, font, 310, 70, 790, 775, "Ticks:", false);

    auto buttons = {&startButton, &stopButton, &stepButton, &runButton,
                    &nFlag, &zFlag, &vFlag, &cFlag, &R0, &R1, &R2, &R3, &R4,
                    &R5, &R6, &R7, &syncButton, &conveyorButton, &ticksButton};

    auto screens = {&byteCodeScreen, &disAsmScreen};

    Emulator::instance().initROM("emulator/rom.raw");
    std::cout << "huy" << std::endl;
    std::cout << Emulator::instance().getRegister(REG_SP) << std::endl;
    std::cout << Emulator::instance().getProcessorStatusWord(PSW_C) << std::endl;
    auto buff = new uint8_t[VIDEO_SIZE];
    Emulator::instance().getVideoMemory(buff, VIDEO_SIZE);

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
                    if (button->rect_.contains(position)) {
                        button->clickHandler();
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color(34, 34, 34));

        for (auto screen: screens) {
            screen->update();
        }
        for (auto button : buttons) {
            button->update();
        }

        for (auto screen: screens) {
            screen->draw();
        }
        for (auto button : buttons) {
            button->draw();
        }

        vRam.draw(buff);

        window.display();
    }
    return 0;
}
