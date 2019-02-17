#include "shakescntrl.h"



    Shakescntrl::Shakescntrl(Game *game){
    shakes.resize(1);
    if (game->randominbegin&&game->evolution)
        shakes[0].randomallweight(game->randommode,game->randomx);
    }

    void Shakescntrl::killall(){shakes.resize(0);}

    void Shakescntrl::resizeshakes(int n){shakes.resize(n);}

    void Shakescntrl::update(World *world,Game *game,vector<sf::Text>& texts){
        std::clog<<std::endl<<std::endl;
        std::clog<<"shakes size= "<<shakes.size();
        if (shakes.size()==0&&game->restart){
            texts[9].setString(to_string(++counterrestarts));
            world->mapsetup();
            shakes.resize(1);
            if (game->randominbegin&game->evolution)
                shakes[0].randomallweight(game->randommode,game->randomx);
        }
        else{
            for (int i=0;i<(int)shakes.size();i++){
                if (shakes[i].getlive()){
                    shakes[i].update(world);

                    if (shakes[i].getdivision()){
                        shakes.resize(shakes.size()+1);
                        shakes[i].setupcordsindevision(shakes[shakes.size()-1]);
                        shakes[i].copyweight(shakes[shakes.size()-1]);
                        if(game->evolution)
                            shakes[i].makeevolution(shakes[shakes.size()-1]);
                        shakes[i].divisionsuccess();
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
