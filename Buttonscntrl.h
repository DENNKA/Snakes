#ifndef BUTTONSCNTRL_H_INCLUDED
#define BUTTONSCNTRL_H_INCLUDED

#include <vector>

#include "Button.h"


class Buttonscntrl{
public:

    std::vector<Button> buttons;
    sf::Texture texturebuttons;

    /*void downtimedelay(Game *game);

    void uptimedelay(Game *game);

    void invertsimulation(Game *game);

    void invertrestart(Game *game);

    void invertevolution(Game *game);

    void invertrandommode(Game *game);*/

    void setupbuttons(int Size,int Size2, int hmap, int wmap);
};

#endif // BUTTONSCNTRL_H_INCLUDED
