#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Game.h"

class Button {
public:
    Button(sf::Texture &texture, sf::Vector2f sbPosition, sf::IntRect sbSprite,bool sswitchable=0);
    void switchcolor();
    void invertvisible();
    sf::Sprite sprite;
    bool visible=1;
private:
    bool switchable;
};

#endif // BUTTON_H_INCLUDED
