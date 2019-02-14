#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED



class World {
public:
    static const int hmap=40,wmap=60; //size map

    void update(int n=1);

    void setmap(int y,int x,char symbol);

    char getmap(int y,int x);

    void mapsetup();

private:

    void setrandom(int k=1);

    int foodi=0;

    char Map[hmap][wmap];

};

#endif // WORLD_H_INCLUDED
