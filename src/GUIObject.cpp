#include "GUIObject.h"
#include <SFML/Graphics.hpp>

GUIObject::GUIObject(sf::RenderWindow *window) : window_(window) {}

void GUIObject::update() {}

void GUIObject::draw() {
    window_->draw(sprite_);
}