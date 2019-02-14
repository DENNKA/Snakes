#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;

class Game{
private:

    int timedelay=0;

public:

    bool simulation=0;
    bool evolution=0;
    bool randominbegin=0;
    bool restart=0;
    bool randommode=0;
    int randomx=0;

    Game(int td=0);

    void setup();

    int gettimedelay();
    void settimedelay(int td);
};

#endif // GAME_H_INCLUDED
