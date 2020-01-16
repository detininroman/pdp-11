#include <SFML/Graphics.hpp>
#include <iostream>

#include "emulator/emulator.hpp"
#include "emulator/params.hpp"
#include "gui/params.hpp"
#include "gui/Screen.hpp"
#include "gui/Button.hpp"
#include "gui/GUIObject.hpp"
#include "gui/text_screen.hpp"
#include "gui/vram_screen.hpp"
#include "misc/bit_array.hpp"


int main(int argc, char *argv[]) {
    std::string binFile = argc > 1 ? argv[1] : "programs/line";

    sf::RenderWindow window(sf::VideoMode(1900, 1350), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/helvetica.ttf");

    VRamScreen vRam(&window, 1050, 600, 50, 50, ScreenType::VRAM_SCREEN);
    TextScreen disAsmScreen(&window, 700, 600, 1150, 700, ScreenType::DISASM_SCREEN, font);
    TextScreen byteCodeScreen(&window, 700, 600, 1150, 50, ScreenType::BYTECODE_SCREEN, font);

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

    bool make_step = true;
    std::string asm_str;
    auto buff = new uint8_t[VIDEO_SIZE];
    Emulator::instance().initROM(binFile);

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

        if (make_step) {
            for (int i = 0; i < 128; i++) {
                Error step_rv = Emulator::instance().step();
                if (step_rv == Error::FINISHED) {
                    make_step = false;
                    std::cout << "FINISHED" << std::endl;

                    break;
                }
            }
            Emulator::instance().getVideoMemory(buff, VIDEO_SIZE);
            BitArray screenBits(buff, VIDEO_SIZE);
        }

        window.clear(darkGray);

        /*
        byteCodeScreen.update();
        disAsmScreen.update();
        vRam.update();
         */

        for (auto button : buttons) {
            button->update();
        }

        for (auto button : buttons) {
            button->draw();
        }

        if (make_step) {
            auto asm_vec = Emulator::instance().getAssemblyCommands(15);
            asm_str.clear();
            for (auto cmd : asm_vec) {
                asm_str += cmd + "\n";
            }
        }

        std::vector <std::string> byte_code_vec;
        std::string byte_code_str;
        for (int i = 0; i < 105; i++) {
            byte_code_vec.push_back("0000");
        }

        int cnt = 1;
        for (auto cmd : byte_code_vec) {
            byte_code_str += cmd + " ";
            if (cnt % 7 == 0) {
                byte_code_str += "\n";
                cnt = 0;
            }
            cnt += 1;
        }

        disAsmScreen.draw(asm_str);
        byteCodeScreen.draw(byte_code_str);
        vRam.draw(buff);

        window.display();
    }
    return 0;
}
