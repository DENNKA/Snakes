#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Buttonscntrl.h"

    class Render{
        public:
            const int Size=15,Size2=1; //size squares

            void render (sf::RenderWindow* window,World* world,int hmap,int wmap);
            void renderbuttonsandtexts (sf::RenderWindow* window,Buttonscntrl *buttonscntrl);
    };

#endif // RENDER_H_INCLUDED
