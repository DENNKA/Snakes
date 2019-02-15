#include "Shake.h"


    int Shake::shakecounter=0;

    Shake::Shake(int sx/*=3*/,int sy/*=3*/){
        x=sx; y=sy;
        shakeid=shakecounter;
        shakecounter++;
        shaketail.resize(shakesize-1);
    }

    void Shake::shakedie(){shakecounter--;}

    void Shake::setxy(int sx,int sy){x=sx; y=sy;}

    bool Shake::getdivision(){return division;}
    bool Shake::getlive(){return live;}
    int Shake::getshakesize(){return shakesize;}
    int Shake::getshakecounter(){return shakecounter;}
    int Shake::getshaketailx(int i){return shaketail[i].x;}
    int Shake::getshaketaily(int i){return shaketail[i].y;}

    void Shake::randomallweight(int mode,int x){
        for (int i=0;i<8;i++){
            for (int j=0;j<7;j++){
                for (int k=0;k<7;k++){
                    switch (mode){
                        case 0:
                            weight[i][j][k]=rand()%x;
                        case 1:
                            weight[i][j][k]+=rand()%x;
                    }
                }
            }
        }
    }

    void Shake::makeevolution(Shake &shake){
        for (int i=0;i<8;i++){
            for (int j=0;j<7;j++){
                for (int k=0;k<7;k++){
                    shake.weight[i][j][k]=weight[i][j][k];
                }
            }
        }
        for (int i=0;i<mutationk;i++){
            shake.weight[rand()%8][rand()%7][rand()%7]+=rand()%mutationx;
        }
    }

    void Shake::divisionsuccess(Shake &shake){
        int j=3;
        shake.lastx=shaketail[shakesize-3].x;
        shake.lasty=shaketail[shakesize-3].y;
        for (int i=shakesize-7;i<shakesize-2;i++){
            if (j!=-1){
                shake.shaketail[j].x=shaketail[i].x;
                shake.shaketail[j].y=shaketail[i].y;
            }
            j--;
        }
        shakesize-=5;
        division=0;
        shaketail.resize(shakesize-1);
    }


    void Shake::addtail(){
        shaketail.resize(shaketail.size()+1);
        shakesize++;
    }

    void Shake::delltail(){
        shaketail.resize(shaketail.size()-1);
        shakesize--;
    }

    void Shake::update(World *world){ //x- left x+ right y- up y+ down
        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                if ((y-3+i)>=0&&(x-3+j)>=0){
                    if ((y-3+i)<world->hmap&&(x-3+j)<world->wmap){
                        switch (world->getmap(y-3+i,x-3+j)){
                            case 'f':
                            case 'd':

                                up+=weight[0][i][j];
                                right+=weight[1][i][j];
                                down+=weight[2][i][j];
                                left+=weight[3][i][j];

                            break;
                            case '0':
                            case 's':

                                up-=weight[4][i][j];
                                right-=weight[5][i][j];
                                down-=weight[6][i][j];
                                left-=weight[7][i][j];

                            break;
                        }
                    }
                }
            }
        }

        std::clog<<" shake id= "<<std::setw(3)<<shakeid<<std::setw(4)<<up<<std::setw(4)<<down<<std::setw(4)<<left<<std::setw(4)<<right;
        std::clog<<"\tsaturarion = "<<saturation<<std::endl;

        if (up>=down&&up>=left&&up>=right){y-=1;}else{
                if (down>=left&&down>=right&&down>=up){y+=1;}else{
                    if (left>=right&&left>=up&&left>=down){x-=1;}else{
                        if (right>=up&&right>=down&&right>=left){x+=1;}}}}

        std::clog<<"y= "<<y<<" x= "<<x<<" shakesize= "<<shakesize<<" shaketail.size= "<<shaketail.size()<<std::endl;

        switch (world->getmap(y,x)){
            case '0':
            case 's':
                live=false;
            break;
            case 'd':
            case 'f':
                saturation++;
            default:
                world->setmap(y,x,'s');
                break;
        }

        up=0;down=0;left=0;right=0;

        world->setmap(shaketail[shakesize-2].y,shaketail[shakesize-2].x,' ');

        for (int i=(shakesize-2);i>0;i--){
            shaketail[i].y=shaketail[i-1].y;
            shaketail[i].x=shaketail[i-1].x;
            std::clog<<std::setw(7)<<i<<std::setw(4)<<shaketail[i].y<<' '<<shaketail[i].x<<std::endl;
            //world->setmap(shaketail[i].y,shaketail[i].x,'s');     //need test
        }

        shaketail[0].y=lasty;
        shaketail[0].x=lastx;
        world->setmap(shaketail[0].y,shaketail[0].x,'s');
        xlasttail=shaketail[shakesize-2].x;ylasttail=shaketail[shakesize-2].y;
        std::clog<<std::setw(7)<<'0'<<std::setw(4)<<shaketail[0].y<<' '<<shaketail[0].x<<std::endl;

        if (saturation>12){
            saturation-=10;
            addtail();
        }

        if (saturation==0){
            saturation+=10;
            world->setmap(ylasttail,xlasttail,' ');
            delltail();
        }

        if (shakesize<4){
            live=0;
        }

        if (hungryi>5){
            hungryi=0;
            saturation--;
        }
        else{ hungryi++; }

        if (shakesize>9){
            division=1;
        }

        lastx=x;lasty=y;

        std::clog<<std::endl;

    }

    void Shake::fillshake(World *world,char symbol){
        world->setmap(y,x,symbol);
        for (auto i=0;i<shakesize-1;i++){
            world->setmap(shaketail[i].y,shaketail[i].x,symbol);
        }
    }

