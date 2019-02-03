//#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/window.hpp>
//#include <SFML/system.hpp>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
#include <string>
#include <iomanip>


#include <boost/numeric/ublas/vector.hpp>

#include "World.h"
//#include "balance.h"
#include "render.h"



using namespace std;


	//RenderWindow window(VideoMode::getDesktopMode(), "shake");
	//sf::RenderWindow* window (new sf::RenderWindow(VideoMode::getDesktopMode(), "shake"));

    //GameWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode( getWindowWidth(), getWindowHeight() ), "Title Goes Here"));

const short Size=20,Size2=1; //size squares



class Game{
    public:

    Game(int td=0){
        timedelay=td;
    }

    void setup(){
        int log=0;
        std::cout<<"Log in console? ";
        std::cin>>log;

        if (log==0){
            std::clog.setstate(std::ios_base::failbit);
        }

        int timedelay;
        std::cout<<"Enter time delay. (during program work use left mouse button to increase time delay, right to decrease)  ";
        std::cin>>timedelay;
        std::cout<<std::endl;
        settimedelay(timedelay);
    }

    void setupwindow(int weight=1000,int height=700){
        //window = new sf::RenderWindow(sf::VideoMode(weight, height), "shake");
        window.reset(new sf::RenderWindow(sf::VideoMode(weight, height), "shake"));
    }

    std::shared_ptr<sf::RenderWindow> getwindow(){return window;}
    int gettimedelay(){return timedelay;}
    void settimedelay(int td){if(td>=0){timedelay=td;}else{timedelay=0;}}

    ~Game(){
    }

    private:
    int timedelay=0;
    std::shared_ptr<sf::RenderWindow> window;
};


class Shake {
private:

public:

    Shake(int sx=3,int sy=3){
    x=sx; y=sy;
    shakeid=shakecounter;
    shakecounter++;
    shaketail.resize(shakesize-1);

}



    bool live=1, division=0;
    short static shakecounter;
    short x=0,y=0,up=0,down=0,left=0,right=0,lastx=0,lasty=0,shakeid,shakesize=5,saturation=8;
    short hungryi=0;

    short weight[8][7][7]={
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
    struct c {
    int x,y;
    };

    boost::numeric::ublas::vector<c>shaketail;

    void shakedie(){shakecounter--;}
    void setxy(int sx,int sy){x=sx; y=sy;}


    bool getdivision(){return division;}
    bool getlive(){return live;}
    short getshakesize(){return shakesize;}
    short getshakecounter(){return shakecounter;}
    int getshaketailx(int i){return shaketail[i].x;}
    int getshaketaily(int i){return shaketail[i].y;}

    void randomallweight(){
        for (int i=0;i<8;i++){
            for (int j=0;j<7;j++){
                for (int k=0;k<7;k++){
                weight[i][j][k]=rand()%2;
                }
            }
        }
    }

    void divisionsuccess(World *world,Shake &shake){
        for (int i=0;i<8;i++){
            for (int j=0;j<7;j++){
                for (int k=0;k<7;k++){
                shake.weight[i][j][k]=weight[i][j][k];
                }
            }
        }
        for (int i=10+rand()%11;i!=0;i--){
            shake.weight[rand()%8][rand()%7][rand()%7]+=rand()%11-5;
        }
        /*for (int j=0;j<7;j++){
            for (int k=0;k<7;k++){
            cout<<setw(4)<<shake.weight[0][j][k]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;*/
        /*int j=3;
        shake.lastx=shaketail[shakesize-3].x;
        shake.lasty=shaketail[shakesize-3].y;*/
        for (int i=shakesize-7;i<shakesize-3;i++){
            std::clog<<"y= "<<shaketail[i].y<<" x= "<<shaketail[i].x<<std::endl;
            world->setmap(shaketail[i].y,shaketail[i].x,' ');
            /*if (j!=-1){
                shake.shaketail[j].x=shaketail[i].x;
                shake.shaketail[j].y=shaketail[i].y;
            }
            j--;*/    //work in progress
        }
        shakesize-=5;
        division=0;
        shaketail.resize(shakesize-1);
    }


    void addtail(){
        shaketail.resize(shaketail.size()+1);
        shakesize++;
    }

    void delltail(World *world){
        world->setmap(shaketail[shaketail.size()-2].y,shaketail[shaketail.size()-2].x,' ');
        shaketail.resize(shaketail.size()-1);
        shakesize--;
    }

    void update(World *world){ //x- left x+ right y- up y+ down
        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                if ((y-3+i)>=0&&(x-3+j)>=0){
                    if ((y-3+i)<hmap&&(x-3+j)<wmap){
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

        std::clog<<std::setw(3)<<shakeid<<std::setw(4)<<up<<std::setw(4)<<down<<std::setw(4)<<left<<std::setw(4)<<right;
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

        //world->setmap(shaketail[shakesize-2].y,shaketail[shakesize-2].x,' ');//bug there

        for (int i=(shakesize-2);i>0;i--){
            shaketail[i].y=shaketail[i-1].y;
            shaketail[i].x=shaketail[i-1].x;
            std::clog<<std::setw(7)<<i<<std::setw(4)<<shaketail[i].y<<' '<<shaketail[i].x<<std::endl;
            world->setmap(shaketail[i].y,shaketail[i].x,'s');
        }

        /*for (int i=0;i<shakesize;i++){
            std::clog<<shaketail[i].x<<' '<<shaketail[i].y<<std::endl;
        }*/
        //Map[shaketail[0].y][shaketail[0].x]=' ';// temporarily
        shaketail[0].y=lasty;
        shaketail[0].x=lastx;
        world->setmap(shaketail[0].y,shaketail[0].x,'s');
        world->setmap(shaketail[shakesize-2].y,shaketail[shakesize-2].x,' ');
        std::clog<<std::setw(7)<<'0'<<std::setw(4)<<shaketail[0].y<<' '<<shaketail[0].x<<std::endl;

        //Map[lasty][lastx]=' '; // temporarily

        if (saturation>12){
            saturation-=10;
            addtail();
        }

        if (saturation==0){
            saturation+=10;
            delltail(world);
        }

        if (shakesize<4){
            live=0;
        }

        if (hungryi>5){hungryi=0;saturation--;}else{hungryi++;}

        if (shakesize>9){
            division=1;
        }

        lastx=x;lasty=y;

        std::clog<<std::endl;
    }

    void fillshake(World *world,char symbol){
        world->setmap(y,x,symbol);
        for (auto i=0;i<shakesize-2;i++){
            world->setmap(shaketail[i].y,shaketail[i].x,symbol);
        }
    }

    ~Shake(){
        //shakecounter--;
    }

};

class Shakescntrl{
    public:
    Shakescntrl(){
    //shakes.resize(1);
    }

    void update(World *world){
        std::clog<<"shakes size= "<<shakes.size();
        if (shakes.size()==0){
            cout<<"Restart!!!\n";
            shakes.resize(1);
            shakes[0].randomallweight();
        }
        else{
            for (int i=0;i<shakes[0].getshakecounter();i++){
                if (shakes[i].getlive()){
                    shakes[i].update(world);

                    if (shakes[i].getdivision()){
                        shakes.resize(shakes[0].getshakecounter()+1);
                        shakes[shakes.size()-1].x=shakes[i].shaketail[shakes[i].getshakesize()-3].x;
                        shakes[shakes.size()-1].y=shakes[i].shaketail[shakes[i].getshakesize()-3].y;
                        shakes[i].divisionsuccess(world,shakes[i+1]);
                    }
                }
                else{
                        shakes[i].fillshake(world,'d');
                        //shakes[i].~Shake();
                        shakes.erase(shakes.begin()+i);
                        shakes[0].shakedie();// decrease shakecounter
                        i--;
                }
            }
        }
    }
    std::vector<Shake> shakes;
};


short Shake::shakecounter=0;

int main(){

    Game game;

    game.setup();

    game.setupwindow();

    World world;

    Shakescntrl shakescntrl;

    render rendershake;

    srand(time(NULL));

	while (game.getwindow()->isOpen()){

		/*float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;*/


		sf::Event event;
		while (game.getwindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.getwindow()->close();
            if (event.mouseButton.button == sf::Mouse::Button::Left)
                game.settimedelay(game.gettimedelay()+5);
            if (event.mouseButton.button == sf::Mouse::Button::Right)
                game.settimedelay(game.gettimedelay()-5);
		}

        std::clog<<std::endl<<std::endl;

        shakescntrl.update(&world);

        world.update();

        rendershake.gorender(game.getwindow(), &world, hmap, wmap, Size, Size2);

		Sleep(game.gettimedelay());
	}
	return 0;
}

