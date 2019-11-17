#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <windows.h>
#include <vector>


class World {
public:
    int hmap=40,wmap=60; //size map

    void mapsetup();
    void update(int n=1);

    void setSize(int _hmap,int _wmap);

    void setmap(int y,int x,char symbol);
    char getmap(int y,int x);
private:
    void setrandom();
    int foodi=0;
    std::vector<std::vector<char>> Map;
    //char Map[hmap][wmap];
};

#endif // WORLD_H_INCLUDED
