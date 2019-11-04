#ifndef PDP_11_SCREEN_H
#define PDP_11_SCREEN_H

#include <SFML/Graphics.hpp>
#include "GUIObject.h"


class Screen : public GUIObject {

public:
    Screen(sf::RenderWindow *window);

    ~Screen() {};
};

#endif //PDP_11_SCREEN_H
