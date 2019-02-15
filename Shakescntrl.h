#ifndef SHAKESCNTRL_H_INCLUDED
#define SHAKESCNTRL_H_INCLUDED

#include "Game.h"
#include "World.h"
#include "Shake.h"


class Shakescntrl{
public:

    void killall();

    void resizeshakes(int n);

    Shakescntrl(Game *game);

    void update(World *world,Game *game,vector<sf::Text>& texts);

private:

    int counterrestarts=0;

    std::vector<Shake> shakes;
};

#endif // SHAKESCNTRL_H_INCLUDED
