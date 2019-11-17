#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <windows.h>
#include <time.h>
#include <fstream>
//#include <thread>
//#include <chrono>
//#include <boost/numeric/ublas/vector.hpp>

#include "World.h"
#include "Render.h"
#include "Game.h"
#include "Snakescntrl.h"
#include "Buttonscntrl.h"
#include "Defines.h"


using namespace std;


#define DEFAULT_WIDTH 1015
#define DEFAULT_HEIGHT 720
#define DEFAULT_WIDTH_MAP 63
#define DEFAULT_HEIGHT_MAP 40
#define DEFAULT_RENDER_SIZE 15
#define DEFAULT_RENDER_SIZE_2 1


int main(){
    Game game;
    game.setup();

    World world;

    Snakescntrl snakescntrl(&game);

    ifstream file("options.txt");
    if (!file.is_open()){
        ofstream file2("options.txt");
        file2<<DEFAULT_WIDTH<<' '<<DEFAULT_HEIGHT<<endl<<DEFAULT_WIDTH_MAP<<' '<<DEFAULT_HEIGHT_MAP<<endl<<DEFAULT_RENDER_SIZE<<' '<<DEFAULT_RENDER_SIZE_2;
        file2<<"\n\n Window width, window height \n Map width, map height \n Size squares, size indent";
        file2<<"\n If you want return default settings delete this file";
        file2.close();
        file.open("options.txt");
    }
    int weight=-1,height=0,wmap=0,hmap=0,Size=0,Size2=0;
    file>>weight>>height>>wmap>>hmap>>Size>>Size2;
    file.close();

    world.setSize(hmap,wmap);
    world.mapsetup();

    Render render;
    render.setsizes(Size,Size2);
    sf::RenderWindow *window=new sf::RenderWindow(sf::VideoMode(weight, height), "Snake");
    glOrtho(0.0,window->getSize().x,window->getSize().y,0.0,1.0,-1.0);
    glEnable(GL_TEXTURE_2D);

    Buttonscntrl buttonscntrl;
    buttonscntrl.setupbuttons(render.Size, render.Size2, world.hmap, world.wmap);
    buttonscntrl.setuptexts(render.Size, render.Size2, world.hmap, world.wmap);

    render.rendersetup(window,&world,&buttonscntrl,&game,&snakescntrl,world.hmap,world.wmap);

    srand(time(NULL));

    #ifdef FPS
    clock_t clockLastFrame=0;
    int framesCounter=0;
    float framesTimeCounter=0;
    int fps=0;
    clockLastFrame=clock();
    //buttonscntrl.texts[buttonscntrl.texts.size()-1].setColor(sf::Color(0,0,0));
    #endif // FPS

	while (window->isOpen()){
        #ifdef FPS
        clock_t clockNow =clock();
        clock_t deltaClock = clockNow - clockLastFrame;
        float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
        clockLastFrame=clockNow;

        framesCounter++;
        framesTimeCounter += deltaTime;
        if( framesTimeCounter >= 1.0 ){
            framesTimeCounter -= 1.0;
            fps = framesCounter;
            framesCounter = 0;
        }
        buttonscntrl.texts[buttonscntrl.texts.size()-1].setString(to_string(fps));
        #endif // FPS
		sf::Event event;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window->close();
				return 0;
			}
			if (event.mouseButton.button == sf::Mouse::Button::Left){
                if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i pos =  sf::Mouse::getPosition(*window);
                    for (auto i=0;i<(int)buttonscntrl.buttons.size();i++){
                        if (buttonscntrl.buttons[i].sprite.getGlobalBounds().contains(pos.x, pos.y)){
                            buttonscntrl.update(i,&game,&snakescntrl,&world,0);
                        }
                    }
                }
			}
            if (event.mouseButton.button == sf::Mouse::Button::Right){
                if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i pos =  sf::Mouse::getPosition(*window);
                    for (auto i=0;i<(int)buttonscntrl.buttons.size();i++){
                        if (buttonscntrl.buttons[i].sprite.getGlobalBounds().contains(pos.x, pos.y)){
                            buttonscntrl.update(i,&game,&snakescntrl,&world,1);
                        }
                    }
                }
            }
		}

        if(game.simulation){
            snakescntrl.update(&world,&game,buttonscntrl.texts);
            world.update(game.foodpertick);
        }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        if(game.rendermap){
            render.rendermap();
        }
        render.renderbuttonsandtexts();
        window->display();
        //std::this_thread::sleep_for(chrono::milliseconds(game.gettimedelay()));
		Sleep(game.gettimedelay());
	}
	return 0;
}

