#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "World.h"
#include "Buttonscntrl.h"
#include "Game.h"
#include "Snakescntrl.h"

    class Render{
        public:
            int Size=15,Size2=1; //size squares

            void setsizes(int sSize,int sSize2);
            void rendersetup(sf::RenderWindow* swindow,World* sworld,Buttonscntrl *sbuttonscntrl,Game* sgame,Snakescntrl* ssnakescntrl,int shmap,int swmap);

            void rendermap();
            void renderbuttonsandtexts();
        private:
            int Size3;
            int hmap;
            int wmap;
            sf::RenderWindow* window;
            Buttonscntrl* buttonscntrl;
            World* world;
            Game* game;
            Snakescntrl* snakescntrl;
    };

#endif // RENDER_H_INCLUDED
