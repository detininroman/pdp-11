#include <SFML/Graphics.hpp>
#include <iostream>

#include "emulator/emulator.hpp"
#include "emulator/params.hpp"
#include "gui/params.hpp"
#include "gui/Screen.hpp"
#include "gui/Button.hpp"
#include "gui/GUIObject.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1900, 1350), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/helvetica.ttf");

    sf::Color darkGray = sf::Color(34, 34, 34);

    Screen vRam(&window, 1050, 600, 50, 50, ScreenType::VRAM_SCREEN);
    Screen byteCodeScreen(&window, 700, 600, 1150, 50, ScreenType::BYTECODE_SCREEN);
    Screen disAsmScreen(&window, 700, 600, 1150, 700, ScreenType::DISASM_SCREEN);

    Button runButton(&window, font, 310, 70, 450, 1150, ButtonType::RUN);
    Button stopButton(&window, font, 310, 70, 450, 1225, ButtonType::STOP);
    Button stepButton(&window, font, 310, 70, 790, 1150, ButtonType::STEP);
    Button startButton(&window, font, 310, 70, 790, 1225, ButtonType::START);

    Button nFlag(&window, font, 70, 70, 450, 775, ButtonType::N_FLAG);
    Button zFlag(&window, font, 70, 70, 530, 775, ButtonType::Z_FLAG);
    Button vFlag(&window, font, 70, 70, 610, 775, ButtonType::V_FLAG);
    Button cFlag(&window, font, 70, 70, 690, 775, ButtonType::C_FLAG);

    Button R0(&window, font, 350, 70, 50, 700, ButtonType::REG0);
    Button R1(&window, font, 350, 70, 50, 775, ButtonType::REG1);
    Button R2(&window, font, 350, 70, 50, 850, ButtonType::REG2);
    Button R3(&window, font, 350, 70, 50, 925, ButtonType::REG3);
    Button R4(&window, font, 350, 70, 50, 1000, ButtonType::REG4);
    Button R5(&window, font, 350, 70, 50, 1075, ButtonType::REG5);
    Button R6(&window, font, 350, 70, 50, 1150, ButtonType::REG6);
    Button R7(&window, font, 350, 70, 50, 1225, ButtonType::REG7);

    Button syncButton(&window, font, 310, 70, 450, 700, ButtonType::SYNC);
    Button conveyorButton(&window, font, 310, 70, 790, 700, ButtonType::CONV);
    Button ticksButton(&window, font, 310, 70, 790, 775, ButtonType::TICKS);

    auto buttons = {&startButton, &stopButton, &stepButton, &runButton, &nFlag, &zFlag, &vFlag, &cFlag,
                    &R0, &R1, &R2, &R3, &R4, &R5, &R6, &R7, &syncButton, &conveyorButton, &ticksButton};

    auto screens = {&byteCodeScreen, &disAsmScreen};

    Emulator::instance().initROM("programs/white_screen");
    for (int i = 0; i < 8194; i++) {
        Emulator::instance().step();
    }
    //std::cout << Emulator::instance().getProcessorStatusWord(PSW_C) << std::endl;

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

        window.clear(darkGray);

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
