#include "World.h"


    void World::setrandom(){
        static int y,x;
        for (int i=0;i<5;i++){
            y=1 + rand() % (hmap-2);
            x=1 + rand() % (wmap-2);
            if (Map[y][x]==' '){
                Map[y][x]='f';
                i=5;
            }
        }
    }

    void World::update(int n/*=1*/){
        if (n==0) return;
        if (n>0){
            for (int i=0;i<n;i++){
                setrandom();
            }
        }
        else{
            foodi++;
            if (foodi>n*-1){
                setrandom();
                foodi=1;
            }
        }
    }

    void World::setSize(int _hmap,int _wmap){
        hmap=_hmap;
        wmap=_wmap;
        Map.resize(hmap);
        for(int i=0;i<hmap;i++)
            Map[i].resize(wmap);
    }

    void World::setmap(int y,int x,char symbol){
        if (Map[y][x]!='0')
            Map[y][x]=symbol;
    }

    char World::getmap(int y,int x){/*if(y<hmap&&x<wmap&&y>=0&&x>=0)*/return Map[y][x];}

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
