#include "snakescntrl.h"



    Snakescntrl::Snakescntrl(Game *game){
    snakes.resize(1);
    if (game->randominbegin&&game->evolution)
        snakes[0].randomallweight(game->randommode,game->getrandomx());
    }

    void Snakescntrl::killall(){snakes.resize(0);}

    void Snakescntrl::resizesnakes(int n){snakes.resize(n);}

    void Snakescntrl::update(World *world,Game *game,vector<sf::Text>& texts){
        #ifdef CLOG
        std::clog<<std::endl<<std::endl;
        std::cout<<"snakes size= "<<snakes.size()<<' ';
        #endif // CLOG
        counterupdates++;
        if(counterupdates>99){
            counterupdates=0;
            std::cout<<snakes.size()<<std::endl;
        }
        if (snakes.size()==0&&game->restart){
            texts[9].setString(to_string(++counterrestarts));
            world->mapsetup();
            snakes.resize(1);
            if (game->randominbegin&game->evolution)
                snakes[0].randomallweight(game->randommode,game->getrandomx());
        }
        else{
            for (int i=0;i<(int)snakes.size();i++){
                if (snakes[i].getlive()){
                    snakes[i].update(world);

                    if (snakes[i].getdivision()){
                        snakes.resize(snakes.size()+1);
                        snakes[i].setupcordsindevision(snakes[snakes.size()-1]);
                        snakes[i].copyweight(snakes[snakes.size()-1]);
                        if(game->evolution)
                            snakes[i].makeevolution(snakes[snakes.size()-1]);
                        snakes[i].divisionsuccess();
                    }
                }
                else{
                        snakes[i].fillsnake(world,'d');
                        //snakes[i].~Snake();
                        snakes.erase(snakes.begin()+i);
                        i--;
                }
            }
        }
    }
