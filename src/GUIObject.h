#ifndef PDP_11_GUIOBJECT_H
#define PDP_11_GUIOBJECT_H

#include <SFML/Graphics.hpp>


class GUIObject {

public:
    sf::RenderWindow *window_;
    sf::Sprite sprite_;

    GUIObject(sf::RenderWindow *window);

    ~GUIObject() {};

    virtual void draw();

    virtual void update();
};

#endif //PDP_11_GUIOBJECT_H
