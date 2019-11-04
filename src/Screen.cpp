#include "Screen.h"
#include "GUIObject.h"
#include <SFML/Graphics.hpp>


Screen::Screen(sf::RenderWindow *window) : GUIObject(window) {
    sf::Texture texture;
    texture.create(1400, 1100);
    sprite_.setTexture(texture);
    sprite_.setPosition(50, 50);
    sprite_.setColor(sf::Color(60, 63, 65));
}
