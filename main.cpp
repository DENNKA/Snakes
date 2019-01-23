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


#include "balance.h"
#include "render.h"



using namespace sf;


	//RenderWindow window(VideoMode::getDesktopMode(), "shake");
	//sf::RenderWindow* window (new sf::RenderWindow(VideoMode::getDesktopMode(), "shake"));

    //GameWindow = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode( getWindowWidth(), getWindowHeight() ), "Title Goes Here"));

const short Size=20,Size2=1; //size squares
const short hmap=25,wmap=40; //size map



class Game{
    public:
    Game(){

        window =new sf::RenderWindow(sf::VideoMode(1000, 700), "shake");

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

    boost::numeric::ublas::vector<c>shaketail;

    void shakedie(){shakecounter--;}
    void setxy(int sx,int sy){x=sx; y=sy;}


    bool getdivision(){return division;}
    bool getlive(){return live;}
    short getshakesize(){return shakesize;}
    short getshakecounter(){return shakecounter;}
    int getshaketailx(int i){return shaketail[i].x;}
    int getshaketaily(int i){return shaketail[i].y;}
    void divisionsuccess(std::string *Map){
        for (int i=shakesize-7;i<shakesize-2;i++){
            std::clog<<"y= "<<shaketail[i].y<<" x= "<<shaketail[i].x<<std::endl;
            Map[shaketail[i].y][shaketail[i].x]=' ';
        }
        shakesize-=5;
        division=0;
        shaketail.resize(shakesize-1);
    }


    void addtail(){
        shaketail.resize(shaketail.size()+1);
        shakesize++;
    }

    void update(std::string *Map){ //x- лево x+ право y- вверх y+ низ

        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                if ((y-3+i)>=0&&(x-3+j)>=0){    //тут вроде баг
                    switch (Map[y-3+i][x-3+j]){
                        case 'f':
                        case 'd':
                            up+=foodup[i][j];
                            down+=fooddown[i][j];
                            left+=foodleft[i][j];
                            right+=foodright[i][j];
                            break;
                        case '0':
                        case 's':
                            up-=wallup[i][j];
                            down-=walldown[i][j];
                            left-=wallleft[i][j];
                            right-=wallright[i][j];
                            break;
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

        switch (Map[y][x]){
            case '0':
            case 's':
                live=false;
            break;
            case 'd':
            case 'f':
                saturation++;
            default:
                Map[y][x]='s';
                break;
        }

        up=0;down=0;left=0;right=0;

        for (int i=(shakesize-2);i>0;i--){
            shaketail[i].y=shaketail[i-1].y;
            shaketail[i].x=shaketail[i-1].x;
            std::clog<<std::setw(7)<<i<<std::setw(4)<<shaketail[i].y<<' '<<shaketail[i].x<<std::endl;
            Map[shaketail[i].y][shaketail[i].x]='s';
        }

        /*for (int i=0;i<shakesize;i++){
            std::clog<<shaketail[i].x<<' '<<shaketail[i].y<<std::endl;
        }*/
        //Map[shaketail[0].y][shaketail[0].x]=' ';// временно
        shaketail[0].y=lasty;
        shaketail[0].x=lastx;
        Map[shaketail[0].y][shaketail[0].x]='s';
        Map[shaketail[shakesize-2].y][shaketail[shakesize-2].x]=' ';
        std::clog<<std::setw(7)<<'0'<<std::setw(4)<<shaketail[0].y<<' '<<shaketail[0].x<<std::endl;

        //Map[lasty][lastx]=' '; // временно

        if (saturation>9){
            saturation-=10;
            addtail();
        }


        if (shakesize>9){
            division=1;
        }

        lastx=x;lasty=y;

        std::clog<<std::endl;
    }

    void fillshake(std::string *Map,char smbl){
        //Map[y][x]=smbl;
        for (auto i=0;i<shakesize-2;i++){
            Map[shaketail[i].y][shaketail[i].x]=smbl;
        }
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
        std::clog<<"shakes size= "<<shakes.size();
        for (int i=0;i<shakes[0].getshakecounter();i++){
            if (shakes[i].getlive()){
                shakes[i].update(Map);

                if (shakes[i].getdivision()){//деление
                    shakes.resize(shakes[0].getshakecounter()+1);

                    shakes[shakes.size()-1].x=shakes[i].shaketail[shakes[i].getshakesize()-3].x;
                    shakes[shakes.size()-1].y=shakes[i].shaketail[shakes[i].getshakesize()-3].y;


                    /*for (int i=(shakes[i].getshakesize()-2);i>5;i--){
                        shakes[i+1].shaketail[i].y=shakes[i].getshaketaily(i);
                        shakes[i+1].shaketail[i].x=shakes[i].getshaketailx(i);
                        //std::clog<<std::setw(7)<<i<<std::setw(4)<<shaketail[i].y<<' '<<shaketail[i].x<<std::endl;
                        Map[shakes[i+1].shaketail[i].y][shakes[i+1].shaketail[i].x]='s'; //error sigsegv
                    }*/
                    shakes[i].divisionsuccess(Map);
                }
            }
            else{
                    shakes[i].fillshake(Map,'d');
                    //shakes[i].~Shake();
                    shakes.erase_element(i);
                    shakes[0].shakedie();// уменьшеает shakecounter
                    i--;
            }
        }
    }

    boost::numeric::ublas::vector<Shake> shakes;
};


short Shake::shakecounter=0;

int main()
{
    {
        int log=0;
        std::cout<<"Log in console? ";
        std::cin>>log;

        if (log==0){
            std::clog.setstate(std::ios_base::failbit);
        }
    }

    int timedelay;
    std::cout<<"Enter time delay. ";
    std::cin>>timedelay;
    std::cout<<std::endl;

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

        std::clog<<std::endl<<std::endl;


        shakescntrl.update(Map);

        world.update(Map);

        rendershake.gorender(Map, hmap, wmap, Size, Size2);

		Sleep(timedelay);
	}
	return 0;
}

