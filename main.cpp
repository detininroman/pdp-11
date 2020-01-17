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
#include "gui/utils.hpp"
#include "misc/bit_array.hpp"


int main(int argc, char *argv[]) {
    std::string binFile = argc > 1 ? argv[1] : "programs/white_screen";

    sf::RenderWindow window(sf::VideoMode(1900, 1350), "PDP-11");

    PDPState state = PDPState::INACTIVE;

    sf::Font font;
    font.loadFromFile("./resources/helvetica.ttf");

    VRamScreen vram_screen(&window, 1050, 600, 50, 50, ScreenType::VRAM_SCREEN);
    TextScreen disasm_screen(&window, 335, 1250, 1515, 50, ScreenType::DISASM_SCREEN, font);
    TextScreen byte_code_screen(&window, 335, 1250, 1150, 50, ScreenType::BYTECODE_SCREEN, font);

    Button execute_button(&window, font, 310, 70, 450, 1150, ButtonType::EXEC);
    Button stop_button(&window, font, 310, 70, 450, 1225, ButtonType::STOP);
    Button step_button(&window, font, 310, 70, 790, 1150, ButtonType::STEP);
    Button start_button(&window, font, 310, 70, 790, 1225, ButtonType::START);
    Button reset_button(&window, font, 310, 70, 450, 1075, ButtonType::RESET);

    Button n_flag(&window, font, 150, 70, 450, 700, ButtonType::N_FLAG);
    Button z_flag(&window, font, 150, 70, 610, 700, ButtonType::Z_FLAG);
    Button v_flag(&window, font, 150, 70, 790, 700, ButtonType::V_FLAG);
    Button c_flag(&window, font, 150, 70, 950, 700, ButtonType::C_FLAG);

    Button ticks_with_pipeline(&window, font, 310, 70, 450, 775, ButtonType::TICKS_PIPE);
    Button ticks_without_pipeline(&window, font, 310, 70, 790, 775, ButtonType::TICKS_NO_PIPE);

    Button R0(&window, font, 350, 70, 50, 700, ButtonType::REG0);
    Button R1(&window, font, 350, 70, 50, 775, ButtonType::REG1);
    Button R2(&window, font, 350, 70, 50, 850, ButtonType::REG2);
    Button R3(&window, font, 350, 70, 50, 925, ButtonType::REG3);
    Button R4(&window, font, 350, 70, 50, 1000, ButtonType::REG4);
    Button R5(&window, font, 350, 70, 50, 1075, ButtonType::REG5);
    Button R6(&window, font, 350, 70, 50, 1150, ButtonType::REG6);
    Button R7(&window, font, 350, 70, 50, 1225, ButtonType::REG7);

    auto buttons = {&start_button, &stop_button, &step_button, &execute_button,
                    &n_flag, &z_flag, &v_flag, &c_flag, &R0, &R1, &R2, &R3, &R4, &R5, &R6, &R7,
                    &ticks_with_pipeline, &ticks_without_pipeline, &reset_button};

    restart:

    auto buff = new uint8_t[VIDEO_SIZE];
    Emulator::instance().initROM(binFile);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                for (auto button : buttons) {
                    if (button->rect.contains(position)) {
                        button->clickHandler();
                        break;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (start_button.rect.contains(position)) {
                        state = PDPState::AUTO;
                    } else if (step_button.rect.contains(position)) {
                        state = PDPState::MANUAL;
                    } else if (stop_button.rect.contains(position)) {
                        state = PDPState::STOPPED;
                    } else if (execute_button.rect.contains(position)) {
                        state = PDPState::EXECUTE;
                    } else if (reset_button.rect.contains(position)) {
                        state = PDPState::INACTIVE;
                        goto restart;
                    }
                }
            }
        }

        window.clear(dark_gray);

        Error step_rv;
        switch (state) {
            case PDPState::EXECUTE:
                for (int i = 0; i < 256; i++) {
                    step_rv = Emulator::instance().step();
                    if (step_rv == Error::FINISHED) {
                        state = PDPState::FINISHED;
                        break;
                    }
                }
                break;
            case PDPState::AUTO:
                step_rv = Emulator::instance().step();
                state = (step_rv != Error::FINISHED) ? PDPState::AUTO : PDPState::FINISHED;
                break;
            case PDPState::MANUAL:
                step_rv = Emulator::instance().step();
                state = (step_rv != Error::FINISHED) ? PDPState::STOPPED : PDPState::FINISHED;
                break;
            default:
                break;
        }

        Emulator::instance().getVideoMemory(buff, VIDEO_SIZE);
        BitArray screenBits(buff, VIDEO_SIZE);

        std::string asm_code;
        std::string byte_code;

        if (state != PDPState::INACTIVE) {
            asm_code = vec2str(Emulator::instance().getAssemblyCommands(33));
            byte_code = vec2str(Emulator::instance().getByteCode(33));
        }

        for (auto button : buttons) {
            button->update();
        }

        disasm_screen.update(asm_code);
        byte_code_screen.update(byte_code);
        vram_screen.update(buff);

        for (auto button : buttons) {
            button->draw();
        }

        disasm_screen.draw();
        byte_code_screen.draw();
        vram_screen.draw();

//        std::cout << states_map[state] << std::endl;
        window.display();
    }

    return 0;
}
