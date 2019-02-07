#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

const int hmap=40,wmap=60; //size map

class World {
    public:

    void update();

    void setmap(int y,int x,char symbol);

    char getmap(int y,int x);

    void mapsetup();

    char Map[hmap][wmap];

};

#endif // WORLD_H_INCLUDED
