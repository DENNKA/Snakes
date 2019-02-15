#include "Button.h"

    void Button::invertvisible(){
        if(visible){visible=0;}else{visible=1;}
    }

    void Button::switchcolor(){
        if(switchable){
            if(sprite.getColor()==sf::Color(255,255,255)){
                sprite.setColor(sf::Color(100,255,0));
            }
            else{
                sprite.setColor(sf::Color(255,255,255));
            }
        }
    }

    Button::Button(sf::Texture &texture, sf::Vector2f sbPosition, sf::IntRect sbSprite,bool sswitchable/*=0*/) {
        switchable=sswitchable;
        sprite.setTexture(texture);
        bPosition = sbPosition;
        bSprite = sbSprite;
        sprite.setTextureRect(bSprite);     //cut texture
        sprite.setPosition(bPosition);      //pos on screen
        sprite.setColor(sf::Color(255,255,255));
    }
