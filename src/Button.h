#ifndef PDP_11_BUTTON_H
#define PDP_11_BUTTON_H

#include <SFML/Graphics.hpp>
#include "GUIObject.h"


class Button : public GUIObject {

public:
    sf::Font font_;
    sf::Text text_;

    Button(sf::RenderWindow *window, sf::Font font);

    ~Button() {};

    void draw();
};

#endif //PDP_11_BUTTON_H


