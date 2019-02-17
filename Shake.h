#ifndef SHAKE_H_INCLUDED
#define SHAKE_H_INCLUDED

#include <vector>
#include <iomanip>
#include <iostream>

#include "World.h"

const int mutationx=5, mutationk=5;



class Shake {
private:

public:

    Shake(int sx=3,int sy=3);

    bool live=1, division=0;
    int static shakecounter;
    int x=0,y=0,up=0,down=0,left=0,right=0,lastx=0,lasty=0,shakeid,shakesize=5,saturation=8;
    int hungryi=0;
    int xlasttail=0,ylasttail=0;

    int weight[8][7][7]={
    {
    {5,5,5,5,5,5,5},
    {5,10,10,10,10,10,5},
    {5,10,20,20,20,10,5},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    },
    {
    {0,0,0,0,5,5,5},
    {0,0,0,0,10,10,5},
    {0,0,0,0,20,10,5},
    {0,0,0,0,20,10,5},
    {0,0,0,0,20,10,5},
    {0,0,0,0,10,10,5},
    {0,0,0,0,5,5,5},
    },
    {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {5,10,20,20,20,10,5},
    {5,10,10,10,10,10,5},
    {5,5,5,5,5,5,5},
    },
    {
    {5,5,5,0,0,0,0},
    {5,10,10,0,0,0,0},
    {5,10,20,0,0,0,0},
    {5,10,20,0,0,0,0},
    {5,10,20,0,0,0,0},
    {5,10,10,0,0,0,0},
    {5,5,5,0,0,0,0},
    },
    {
    {1,1,1,1,1,1,1},
    {1,1,1,5,1,1,1},
    {1,1,5,20,5,1,1},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    },
    {
    {0,0,0,0,1,1,1},
    {0,0,0,0,1,1,1},
    {0,0,0,0,5,1,1},
    {0,0,0,0,20,5,1},
    {0,0,0,0,5,1,1},
    {0,0,0,0,1,1,1},
    {0,0,0,0,1,1,1},
    },
    {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {1,1,5,20,5,1,1},
    {1,1,1,5,1,1,1},
    {1,1,1,1,1,1,1},
    },
    {
    {1,1,1,0,0,0,0},
    {1,1,1,0,0,0,0},
    {1,1,5,0,0,0,0},
    {1,5,20,0,0,0,0},
    {1,1,5,0,0,0,0},
    {1,1,1,0,0,0,0},
    {1,1,1,0,0,0,0},
    }
    };

    struct xy {
    int x,y;
    };
    std::vector<xy>shaketail;

    void shakedie();
    void setxy(int sx,int sy);
    bool getdivision();
    bool getlive();
    int getshakesize();
    int getshakecounter();
    int getshaketailx(int i);
    int getshaketaily(int i);

    void randomallweight(int mode,int x);
    void setupcordsindevision(Shake &shake);
    void copyweight(Shake &shake);
    void makeevolution(Shake &shake);
    void divisionsuccess();

    void addtail();
    void delltail();

    void update(World *world);

    void fillshake(World *world,char symbol);

};

#endif // SHAKE_H_INCLUDED
