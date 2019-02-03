#include "render.h"

    void World::update(){
        int y =1 + rand() % (hmap-2);
        int x =1 + rand() % (wmap-2);
        if (Map[y][x]==' ')
            Map[y][x]='f';
    }

    void World::setmap(int y,int x,char symbol){
        if (Map[y][x]!='0')
            Map[y][x]=symbol;
    }

    char World::getmap(int y,int x){return Map[y][x];}
