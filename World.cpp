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

    char World::getmap(int y,int x){if(y<hmap&&x<wmap&&y>=0&&x>=0)return Map[y][x];}

    void World::mapsetup(){
        for (int i=0;i<hmap;i++){
            for (int j=0;j<wmap;j++){
                Map[i][j]=' ';
            }
        }
        for (int i=0;i<hmap;i++){
            Map[i][0]='0';
            Map[i][wmap-1]='0';
        }
        for (int i=0;i<wmap;i++){
            Map[0][i]='0';
            Map[hmap-1][i]='0';
        }
    }
