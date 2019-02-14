#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "Game.h"

class Button {
public:

    void (*func) (Game *game);

    void switchcolor();

    Button(sf::Texture &texture, sf::Vector2f sbPosition, sf::IntRect sbSprite,void (*sfunc)(Game *game),bool sswitchable=0);

    sf::Sprite sprite;

private:

    sf::Vector2f bPosition;    //pos on screen
    sf::IntRect bSprite;    //cord on texture

    bool switchable;
};

#endif // BUTTON_H_INCLUDED
