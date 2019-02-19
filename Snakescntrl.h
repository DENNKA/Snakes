#ifndef SHAKESCNTRL_H_INCLUDED
#define SHAKESCNTRL_H_INCLUDED

#include "Game.h"
#include "World.h"
#include "Snake.h"


class Snakescntrl{
public:
    Snakescntrl(Game *game);
    void update(World *world,Game *game,vector<sf::Text>& texts);
    void killall();
    void resizesnakes(int n);
private:
    int counterrestarts=0;
    std::vector<Snake> snakes;
};

#endif // SHAKESCNTRL_H_INCLUDED
