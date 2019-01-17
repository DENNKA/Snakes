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


#include "balance.h"
#include "render.h"


using namespace sf;


	//RenderWindow window(VideoMode::getDesktopMode(), "shake");
	//sf::RenderWindow* window (new sf::RenderWindow(VideoMode::getDesktopMode(), "shake"));

    //GameWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode( getWindowWidth(), getWindowHeight() ), "Title Goes Here"));

const short Size=20,Size2=1; //size squares
const short hmap=25,wmap=40; //size map
const short timedelay=1;//100



class Game{
    public:
    Game(){

        window =new sf::RenderWindow(VideoMode::getDesktopMode(), "shake");

    }

    sf::RenderWindow* getwindow(){return window;}
    sf::RenderWindow* window;
};
class World {
    public:
    int update(std::string *Map){
        Map[1 + rand() % (hmap-2)][1 + rand() % (wmap-2)]='f';
        return 0;
    }
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
    short x=0,y=0,up=0,down=0,left=0,right=0,lastx=0,lasty=0,shakeid,shakesize=5,saturation=0;

    struct c {
    int x,y;
    };

    std::vector<c>shaketail;

    void shakedie(){shakecounter--;}
    void setxy(int sx,int sy){x=sx; y=sy;}


    bool getdivision(){return division;}
    bool getlive(){return live;}
    short getshakesize(){return shakesize;}
    short getshakecounter(){return shakecounter;}
    int getshaketailx(int i){return shaketail[i].x;}
    int getshaketaily(int i){return shaketail[i].y;}
    void divisionsuccess(){
        shakesize-=5;
        division=0;
        shaketail.erase(shaketail.end()-5,shaketail.end());
    }


    void addtail(std::vector<c> &shaketail){
        shaketail.resize(shaketail.size()+1);
        shakesize++;
    }

    void update(std::string *Map){ //x- лево x+ право y- вверх y+ низ

        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                if ((y-3+i)>=0&&(x-3+j)>=0){    //тут вроде баг
                    if (Map[y-3+i][x-3+j] == 'f'){
                        up+=foodup[i][j];
                        down+=fooddown[i][j];
                        left+=foodleft[i][j];
                        right+=foodright[i][j];
                    }
                    if (Map[y-3+i][x-3+j] == '0'||Map[y-3+i][x-3+j] == 's'){
                        up-=wallup[i][j];
                        down-=walldown[i][j];
                        left-=wallleft[i][j];
                        right-=wallright[i][j];
                    }
                }
            }
        }

        std::cout<<std::setw(3)<<shakeid<<std::setw(4)<<up<<std::setw(4)<<down<<std::setw(4)<<left<<std::setw(4)<<right;
        std::cout<<"\tsaturarion = "<<saturation<<std::endl;

        if (up>=down&&up>=left&&up>=right){y-=1;}else{
                if (down>=left&&down>=right&&down>=up){y+=1;}else{
                    if (left>=right&&left>=up&&left>=down){x-=1;}else{
                        if (right>=up&&right>=down&&right>=left){x+=1;}}}}

        std::cout<<"y= "<<y<<" x= "<<x<<" shakesize= "<<shakesize<<" shaketail.size= "<<shaketail.size()<<std::endl;

        switch (Map[y][x]){
            case '0':
            case 's':
                live=false;
                break;
            case 'f':
                saturation++;
                break;
        }

        Map[y][x]='s';
        up=0;down=0;left=0;right=0;


        for (int i=(shakesize-1);i>0;i--){
            shaketail[i].y=shaketail[i-1].y;
            shaketail[i].x=shaketail[i-1].x;
            std::cout<<std::setw(7)<<i<<std::setw(4)<<shaketail[i].y<<' '<<shaketail[i].x<<std::endl;
            Map[shaketail[i].y][shaketail[i].x]='s';
        }

        /*for (int i=0;i<shakesize;i++){
            std::cout<<shaketail[i].x<<' '<<shaketail[i].y<<std::endl;
        }*/
        //Map[shaketail[0].y][shaketail[0].x]=' ';// временно
        shaketail[0].y=lasty;
        shaketail[0].x=lastx;
        Map[shaketail[0].y][shaketail[0].x]='s';
        Map[shaketail[shakesize-1].y][shaketail[shakesize-1].x]=' ';
        std::cout<<std::setw(7)<<'0'<<std::setw(4)<<shaketail[0].y<<' '<<shaketail[0].x<<std::endl;

        //Map[lasty][lastx]=' '; // временно

        if (saturation>9){
            saturation-=10;
            addtail(shaketail);
        }


        if (shakesize>9){
            division=1;
        }

        lastx=x;lasty=y;

        std::cout<<std::endl;
    }

    ~Shake(){
        //shakecounter--;
    }

};

class Shakescntrl{
    public:
    Shakescntrl(){
    shakes.resize(1);
    /*shakes.resize(2);
    shakes[1].x=10;
    shakes[1].y=10;*/
    }
    void update(std::string *Map){
        std::cout<<"shakes size= "<<shakes.size();
        for (int i=0;i<shakes[0].getshakecounter();i++){
            if (shakes[i].getlive()){
                shakes[i].update(Map);

                if (shakes[i].getdivision()){//деление
                    //shakes.resize(shakes[0].getshakecounter()+1);

                    /*shakes[i+1].x=shakes[i].getshaketailx(shakes[i].getshakesize()-2);
                    shakes[i+1].y=shakes[i].getshaketaily(shakes[i].getshakesize()-2);
                    std::cout<<" ======= "<<shakes[i].getshakesize()-2<<" ==== "<<shakes[i].getshaketailx(shakes[i].getshakesize()-2);*/


                    /*for (int i=(shakes[i].getshakesize()-2);i>5;i--){
                        shakes[i+1].shaketail[i].y=shakes[i].getshaketaily(i);
                        shakes[i+1].shaketail[i].x=shakes[i].getshaketailx(i);
                        //std::cout<<std::setw(7)<<i<<std::setw(4)<<shaketail[i].y<<' '<<shaketail[i].x<<std::endl;
                        Map[shakes[i+1].shaketail[i].y][shakes[i+1].shaketail[i].x]='s'; //error sigsegv
                    }*/
                    //shakes[i].divisionsuccess();
                }
            }
            else{
                    shakes[i].~Shake();
                    shakes.erase(shakes.begin() + i);
                    shakes[0].shakedie();// уменьшеает shakecounter
                    //i--;
            }
        }
    }
    std::vector<Shake> shakes;
};


short Shake::shakecounter=0;

int main()
{
    srand(time(NULL));
    std::string Map [hmap+5] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};
    //setFrameLimit(60);
	//float CurrentFrame = 0;

	//Clock clock;

    //rectangle.setSize(Vector2f(Size, Size));
    Game game;

    World world;

    Shakescntrl shakescntrl;

    render rendershake(game.getwindow());



	while (game.getwindow()->isOpen()){

		/*float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;*/


		sf::Event event;
		while (game.getwindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.getwindow()->close();
		}

        std::cout<<std::endl<<std::endl;


        shakescntrl.update(Map);

        world.update(Map);

        rendershake.gorender(Map, hmap, wmap, Size, Size2);

		Sleep(timedelay);
	}
	return 0;
}

