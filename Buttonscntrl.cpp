#include "Buttonscntrl.h"



    void downtimedelay(Game *game){
        game->settimedelay(game->gettimedelay()-10);
    }

    void uptimedelay(Game *game){
        game->settimedelay(game->gettimedelay()+10);
    }

    void invertsimulation(Game *game){
        if(game->simulation){game->simulation=0;}else{game->simulation=1;}
    }

    void invertrestart(Game *game){
        if(game->restart){game->restart=0;}else{game->restart=1;}
    }

    void invertevolution(Game *game){
        if(game->evolution){game->evolution=0;}else{game->evolution=1;}
    }

    void invertrandominbegin(Game *game){
        if(game->randominbegin){game->randominbegin=0;}else{game->randominbegin=1;}
    }

    void invertrandommode(Game *game){
        if(game->randommode){game->randommode=0;}else{game->randommode=1;}
    }

    void Buttonscntrl::setupbuttons(int Size,int Size2, int hmap, int wmap){
        texturebuttons.loadFromFile("img/buttons.png");
        buttons.push_back(Button(texturebuttons,sf::Vector2f( Size+Size2 , hmap * (Size+Size2)),sf::IntRect(0,0,64,64),downtimedelay));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(2 * (Size+Size2) + 64 , hmap * (Size+Size2) ),sf::IntRect(64,0,64,64),uptimedelay));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(3 * (Size+Size2) + 2*64 , hmap * (Size+Size2) ),sf::IntRect(2*64,0,64,64),invertsimulation,1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(4 * (Size+Size2) + 3*64 , hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),invertrestart,1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(4 * (Size+Size2) + 3*64 , 33 + hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),invertevolution,1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(5 * (Size+Size2) + 5*64 , hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),invertrandominbegin,1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(5 * (Size+Size2) + 5*64 , 33 + hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),invertrandommode,1));
    }
