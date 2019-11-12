#include <SFML/Graphics.hpp>

#include "gui/Screen.hpp"
#include "gui/Button.hpp"
#include "gui/GUIObject.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1400), "PDP-11");

    sf::Font font;
    font.loadFromFile("./resources/font.ttf");

    Screen screen(&window);
    Button button(&window, font);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear(sf::Color(43, 43, 43));

        screen.update();
        button.update();

        screen.draw();
        button.draw();

        window.display();
    }
    return 0;
}
