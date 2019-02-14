#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/window.hpp>
//#include <SFML/system.hpp>
#include <windows.h>
#include <time.h>


//#include <boost/numeric/ublas/vector.hpp>


#include "World.h"
#include "render.h"
#include "Game.h"
#include "Shakescntrl.h"
#include "Buttonscntrl.h"


using namespace std;


int main(){

    Game game;

    game.setup();

    World world;

    world.mapsetup();

    Shakescntrl shakescntrl(&game);

    Render render;

    sf::RenderWindow *window=new sf::RenderWindow(sf::VideoMode(1000, 710), "shake");

    Buttonscntrl buttonscntrl;

    buttonscntrl.setupbuttons(render.Size, render.Size2, world.hmap, world.wmap);

    srand(time(NULL));

	while (window->isOpen()){

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
                            buttonscntrl.buttons[i].func(&game);
                            buttonscntrl.buttons[i].switchcolor();
                        }
                    }
                }
            }
		}

        if(game.simulation){
            shakescntrl.update(&world,&game);
            world.update(game.foodpertick);
        }

        window->clear();

        render.gorender(window, &world, world.hmap, world.wmap);

        for(int i=0;i<(int)buttonscntrl.buttons.size();i++){
            window->draw(buttonscntrl.buttons[i].sprite);
        }

        window->display();

		Sleep(game.gettimedelay());
	}
	return 0;
}

