#include "shakescntrl.h"



    Shakescntrl::Shakescntrl(Game *game){
    shakes.resize(1);
    if (game->randominbegin)
        shakes[0].randomallweight(game->randommode,10);
    }

    void Shakescntrl::update(World *world,Game *game){
        std::clog<<std::endl<<std::endl;
        std::clog<<"shakes size= "<<shakes.size();
        if (shakes.size()==0&&game->restart){
            cout<<"Restart! # "<<++counterrestarts<<endl;
            shakes.resize(1);
            if (game->randominbegin)
                shakes[0].randomallweight(game->randommode,game->randomx);
        }
        else{
            for (int i=0;i<(int)shakes.size();i++){
                if (shakes[i].getlive()){
                    shakes[i].update(world);

                    if (shakes[i].getdivision()){
                        shakes.resize(shakes.size()+1);
                        shakes[shakes.size()-1].x=shakes[i].shaketail[shakes[i].getshakesize()-3].x;
                        shakes[shakes.size()-1].y=shakes[i].shaketail[shakes[i].getshakesize()-3].y;
                        if(game->evolution)
                            shakes[i].makeevolution(shakes[shakes.size()-1]);
                        shakes[i].divisionsuccess(shakes[shakes.size()-1]);
                    }
                }
                else{
                        shakes[i].fillshake(world,'d');
                        //shakes[i].~Shake();
                        shakes.erase(shakes.begin()+i);
                        i--;
                }
            }
        }
    }
