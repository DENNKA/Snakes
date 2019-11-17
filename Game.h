#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;

class Game{
public:
    void setup();

    bool simulation=0;
    bool evolution=0;
    bool randominbegin=0;
    bool restart=0;
    bool randommode=0;
    bool rendermap=1;
    int foodpertick=1;

    int getrandomx();
    void setrandomx(int rndx);
    int gettimedelay();
    void settimedelay(int td);
private:
    int timedelay=10;  //in milliseconds
    int randomx=3;
};

#endif // GAME_H_INCLUDED
