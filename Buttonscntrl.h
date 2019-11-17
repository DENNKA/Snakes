#ifndef BUTTONSCNTRL_H_INCLUDED
#define BUTTONSCNTRL_H_INCLUDED

#include <vector>
#include <string>

#include "Button.h"
#include "Snakescntrl.h"
#include "Defines.h"


class Buttonscntrl{     //Text and buttons
public:
    void setuptexts(int Size,int Size2, int hmap, int wmap, int Size3=20);
    void setupbuttons(int Size,int Size2, int hmap, int wmap);

    void update(int &i,Game *game,Snakescntrl *snakescntrl,World *world,bool mode);

    std::vector<sf::Text> texts;
    std::vector<Button> buttons;
private:
    sf::Font font;
    sf::Texture texturebuttons;
};

#endif // BUTTONSCNTRL_H_INCLUDED
