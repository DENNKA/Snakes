#include "Game.h"


    void Game::setup(){
        //std::clog.setstate(std::ios_base::failbit);
        /*int log=0;
        std::cout<<"Log in console? ";
        std::cin>>log;

        if (log==0){
            std::clog.setstate(std::ios_base::failbit);
        }

        int timedelay;
        std::cout<<"Enter time delay. (during program work use left mouse button to increase time delay, right to decrease)  ";
        std::cin>>timedelay;
        settimedelay(timedelay);*/

        /*cout<<"If all snakes die restart game? (recommended 1) ";
        cin>>restart;

        cout<<"On evolution? ";
        cin>>evolution;

        if (evolution){

            cout<<"randome in begin? ";
            cin>>randominbegin;

            if (randominbegin){

                cout<<"relative random? (if 0 random be absolute) ";
                cin>>randommode;
                cout<<"How hard randome? ";
                cin>>randomx;
            }
        }*/
    }


    int Game::getrandomx(){return randomx;}
    void Game::setrandomx(int rndx){
        if(rndx==0){
            if(randomx>0){randomx=-1;}else{randomx=1;}
        }
        else{
            randomx=rndx;
        }
    }
    int Game::gettimedelay(){return timedelay;}
    void Game::settimedelay(int td){if(td>=0){timedelay=td;}else{timedelay=0;}}

