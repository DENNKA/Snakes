#ifndef SHAKESCNTRL_H_INCLUDED
#define SHAKESCNTRL_H_INCLUDED

#include "Game.h"
#include "World.h"
#include "Snake.h"
#include "Defines.h"

class Snakescntrl{
public:
    Snakescntrl(Game *game);
    void update(World *world,Game *game,vector<sf::Text>& texts);
    void killall();
    void resizesnakes(int n);
    std::vector<Snake> snakes;
private:
    int counterupdates=0;
    int counterrestarts=0;
};

#endif // SHAKESCNTRL_H_INCLUDED
