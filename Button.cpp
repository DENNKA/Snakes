#include "Button.h"


    void Button::switchcolor(){
        if(switchable){
            if(sprite.getColor()==sf::Color(255,255,255)){
                sprite.setColor(sf::Color(102,255,0));
            }
            else{
                sprite.setColor(sf::Color(255,255,255));
            }
        }
    }

    Button::Button(sf::Texture &texture, sf::Vector2f sbPosition, sf::IntRect sbSprite,void (*sfunc)(Game *game),bool sswitchable/*=0*/) {
        switchable=sswitchable;
        func=sfunc;
        sprite.setTexture(texture);
        bPosition = sbPosition;
        bSprite = sbSprite;
        sprite.setTextureRect(bSprite);     //cut texture
        sprite.setPosition(bPosition);      //pos on screen
        sprite.setColor(sf::Color(255,255,255));
    }
