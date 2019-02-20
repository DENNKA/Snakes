#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/window.hpp>
//#include <SFML/system.hpp>
#include <windows.h>
#include <time.h>
#include <fstream>

//#include <boost/numeric/ublas/vector.hpp>


#include "World.h"
#include "Render.h"
#include "Game.h"
#include "Snakescntrl.h"
#include "Buttonscntrl.h"
#include "Defines.h"


using namespace std;


#define DEFAULT_WEIGHT 1000
#define DEFAULT_HEIGHT 710
#define DEFAULT_WEIGHT_MAP 60
#define DEFAULT_HEIGHT_MAP 40



int main(){
    Game game(10);
    game.setup();

    World world;
    world.mapsetup();

    Snakescntrl snakescntrl(&game);

    ifstream file("options.txt");
    if (!file.is_open()){
        ofstream file2("options.txt");
        file2<<DEFAULT_WEIGHT<<' '<<DEFAULT_HEIGHT/*<<endl<<DEFAULT_WEIGHT_MAP<<' '<<DEFAULT_HEIGHT_MAP*/;
        file2.close();
        file.open("options.txt");
    }
    int weight=0,height=0;
    file>>weight>>height/*>>wmap>>hmap*/;
    file.close();

    Render render;
    sf::RenderWindow *window=new sf::RenderWindow(sf::VideoMode(weight, height), "Snake");

    Buttonscntrl buttonscntrl;
    buttonscntrl.setupbuttons(render.Size, render.Size2, world.hmap, world.wmap);
    buttonscntrl.setuptexts(render.Size, render.Size2, world.hmap, world.wmap);

    srand(time(NULL));

    #ifdef FPS
    clock_t clockLastFrame=0;
    int framesCounter=0;
    float framesTimeCounter=0;
    int fps=0;
    clockLastFrame=clock();
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
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Button::Left){
                    sf::Vector2i pos =  sf::Mouse::getPosition(*window);
                    for (auto i=0;i<(int)buttonscntrl.buttons.size();i++){
                        if (buttonscntrl.buttons[i].sprite.getGlobalBounds().contains(pos.x, pos.y)){
                            buttonscntrl.update(i,&game,&snakescntrl,&world);
                        }
                    }
                }
            }
		}

        if(game.simulation){
            snakescntrl.update(&world,&game,buttonscntrl.texts);
            world.update(game.foodpertick);
        }

        window->clear();
        render.render(window, &world, world.hmap, world.wmap);
        render.renderbuttonsandtexts(window,&buttonscntrl);
        window->display();

		Sleep(game.gettimedelay());
	}
	return 0;
}

