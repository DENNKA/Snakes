#include "Snake.h"


    int Snake::snakecounter=0;

    Snake::Snake(int sx/*=3*/,int sy/*=3*/){
        x=sx; y=sy;
        snakeid=snakecounter;
        snakecounter++;
        snaketail.resize(snakesize-1);
    }

    void Snake::snakedie(){snakecounter--;}
    void Snake::setxy(int sx,int sy){x=sx; y=sy;}
    int Snake::getx(){return x;}
    int Snake::gety(){return y;}
    bool Snake::getdivision(){return division;}
    bool Snake::getlive(){return live;}
    int Snake::getsnakesize(){return snakesize;}
    int Snake::getsnakecounter(){return snakecounter;}
    int Snake::getsnaketailx(int i){return snaketail[i].x;}
    int Snake::getsnaketaily(int i){return snaketail[i].y;}

    void Snake::randomallweight(int mode,int x){
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

    void Snake::setupcordsindevision(Snake &snake){
        snake.x=snaketail[snakesize-3].x;
        snake.y=snaketail[snakesize-3].y;
        snake.lastx=snaketail[snakesize-3].x;
        snake.lasty=snaketail[snakesize-3].y;
        int j=3;
        for (int i=snakesize-7;i<snakesize-2;i++){
            if (j!=-1){
                snake.snaketail[j].x=snaketail[i].x;
                snake.snaketail[j].y=snaketail[i].y;
            }
            j--;
        }
    }

    void Snake::copyweight(Snake &snake){
        for (int i=0;i<8;i++){
            for (int j=0;j<7;j++){
                for (int k=0;k<7;k++){
                    snake.weight[i][j][k]=weight[i][j][k];
                }
            }
        }
    }

    void Snake::makeevolution(Snake &snake){
        if (rand()%mutationk==0){
            snake.weight[rand()%8][rand()%7][rand()%7]+=rand()%mutationx;
            /*for(int i=0;i<7;i++)
                std::cout<<snake.weight[0][0][i]<<' ';
            std::cout<<std::endl;*/
        }
        /*for (int i=0;i<mutationk;i++){
            snake.weight[rand()%8][rand()%7][rand()%7]+=rand()%mutationx;
        }*/
    }

    void Snake::divisionsuccess(){
        snakesize-=5;
        division=0;
        snaketail.resize(snakesize-1);
    }


    void Snake::addtail(){
        snaketail.resize(snaketail.size()+1);
        snakesize++;
    }

    void Snake::delltail(){
        snaketail.resize(snaketail.size()-1);
        snakesize--;
    }

    void Snake::update(World *world){ //x- left x+ right y- up y+ down
        up=0;down=0;left=0;right=0;

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

        if (up>=down&&up>=left&&up>=right){y-=1;}else{
                if (down>=left&&down>=right&&down>=up){y+=1;}else{
                    if (left>=right&&left>=up&&left>=down){x-=1;}else{
                        if (right>=up&&right>=down&&right>=left){x+=1;}}}}

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

        world->setmap(snaketail[snakesize-2].y,snaketail[snakesize-2].x,' ');

        for (int i=(snakesize-2);i>0;i--){      //move tail to head
            snaketail[i].y=snaketail[i-1].y;
            snaketail[i].x=snaketail[i-1].x;
        }

        snaketail[0].y=lasty;
        snaketail[0].x=lastx;

        xlasttail=snaketail[snakesize-2].x;ylasttail=snaketail[snakesize-2].y;

        if (saturation>12){
            saturation-=10;
            addtail();
        }

        if (saturation==0){
            saturation+=10;
            world->setmap(ylasttail,xlasttail,' ');
            delltail();
        }

        if (snakesize<4){
            live=0;
        }

        if (hungryi>5){
            hungryi=0;
            saturation--;
        }
        else{ hungryi++; }

        if (snakesize>9){
            division=1;
        }

        lastx=x;lasty=y;

        #ifdef CLOG
        std::clog<<" snake id= "<<std::setw(3)<<snakeid<<std::setw(4)<<up<<std::setw(4)<<down<<std::setw(4)<<left<<std::setw(4)<<right;
        std::clog<<"\tsaturarion = "<<saturation<<std::endl;
        std::clog<<"y= "<<y<<" x= "<<x<<" snakesize= "<<snakesize<<" snaketail.size= "<<snaketail.size()<<std::endl;
        for(int i=0;i<snaketail.size();i++){
            std::clog<<std::setw(7)<<i<<std::setw(4)<<snaketail[i].y<<' '<<snaketail[i].x<<std::endl;
        }
        std::clog<<std::endl;
        #endif // CLOG
    }

    void Snake::fillsnake(World *world,char symbol){
        world->setmap(y,x,symbol);
        for (auto i=0;i<snakesize-1;i++){
            world->setmap(snaketail[i].y,snaketail[i].x,symbol);
        }
    }

