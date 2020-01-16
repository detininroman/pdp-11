#include <SFML/Graphics.hpp>
#include <iostream>

#include "emulator/emulator.hpp"
#include "emulator/params.hpp"
#include "gui/params.hpp"
#include "gui/screen.hpp"
#include "gui/button.hpp"
#include "gui/GUI_object.hpp"
#include "gui/text_screen.hpp"
#include "gui/vram_screen.hpp"
#include "misc/bit_array.hpp"


int main(int argc, char *argv[]) {
    std::string binFile = argc > 1 ? argv[1] : "programs/line";

    sf::RenderWindow window(sf::VideoMode(1900, 1350), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/helvetica.ttf");

    VRamScreen vram_screen(&window, 1050, 600, 50, 50, ScreenType::VRAM_SCREEN);
    TextScreen disasm_screen(&window, 335, 1250, 1515, 50, ScreenType::DISASM_SCREEN, font);
    TextScreen byte_code_screen(&window, 335, 1250, 1150, 50, ScreenType::BYTECODE_SCREEN, font);

    Button run_button(&window, font, 310, 70, 450, 1150, ButtonType::RUN);
    Button stop_button(&window, font, 310, 70, 450, 1225, ButtonType::STOP);
    Button step_button(&window, font, 310, 70, 790, 1150, ButtonType::STEP);
    Button start_button(&window, font, 310, 70, 790, 1225, ButtonType::START);

    Button n_flag(&window, font, 150, 70, 450, 775, ButtonType::N_FLAG);
    Button z_flag(&window, font, 150, 70, 610, 775, ButtonType::Z_FLAG);
    Button v_flag(&window, font, 150, 70, 790, 775, ButtonType::V_FLAG);
    Button c_flag(&window, font, 150, 70, 950, 775, ButtonType::C_FLAG);

    Button R0(&window, font, 350, 70, 50, 700, ButtonType::REG0);
    Button R1(&window, font, 350, 70, 50, 775, ButtonType::REG1);
    Button R2(&window, font, 350, 70, 50, 850, ButtonType::REG2);
    Button R3(&window, font, 350, 70, 50, 925, ButtonType::REG3);
    Button R4(&window, font, 350, 70, 50, 1000, ButtonType::REG4);
    Button R5(&window, font, 350, 70, 50, 1075, ButtonType::REG5);
    Button R6(&window, font, 350, 70, 50, 1150, ButtonType::REG6);
    Button R7(&window, font, 350, 70, 50, 1225, ButtonType::REG7);

    Button sync_button(&window, font, 310, 70, 450, 700, ButtonType::SYNC);
    Button conveyor_button(&window, font, 310, 70, 790, 700, ButtonType::CONV);
    Button ticks_button(&window, font, 310, 70, 790, 850, ButtonType::TICKS);

    auto buttons = {&start_button, &stop_button, &step_button, &run_button, &n_flag, &z_flag, &v_flag, &c_flag,
                    &R0, &R1, &R2, &R3, &R4, &R5, &R6, &R7, &sync_button, &conveyor_button, &ticks_button};

    bool make_step = true;
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

        std::string asm_str;
        auto asm_vec = Emulator::instance().getAssemblyCommands(33);
        for (auto cmd : asm_vec) {
            asm_str += cmd + "\n";
        }

        // TODO: create similar interface
        std::string byte_code_str;
        auto byte_code_vec = Emulator::instance().getByteCode();
        auto size = byte_code_vec.size();
        for (int i = size - 33; i < size; i++) {
            byte_code_str += byte_code_vec[i] + "\n";
        }

        disasm_screen.draw(asm_str);
        byte_code_screen.draw(byte_code_str);
        vram_screen.draw(buff);

        window.display();
    }
    return 0;
}
