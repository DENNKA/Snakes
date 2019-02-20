#ifndef BUTTONSCNTRL_H_INCLUDED
#define BUTTONSCNTRL_H_INCLUDED

#include <vector>
#include <string>

#include "Button.h"
#include "Snakescntrl.h"
#include "Defines.h"


class Buttonscntrl{     //Text and buttons
public:
    std::vector<sf::Text> texts;
    sf::Font font;
    std::vector<Button> buttons;
    sf::Texture texturebuttons;

    void update(int &i,Game *game,Snakescntrl *snakescntrl,World *world);

    /*void downtimedelay(Game *game);
    void uptimedelay(Game *game);
    void invertsimulation(Game *game);
    void invertrestart(Game *game);
    void invertevolution(Game *game);
    void invertrandommode(Game *game);*/

    void setuptexts(int Size,int Size2, int hmap, int wmap, int Size3=20);
    void setupbuttons(int Size,int Size2, int hmap, int wmap);
};

#endif // BUTTONSCNTRL_H_INCLUDED
