#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include "World.h"

    class Render{
        public:
            const int Size=15,Size2=1; //size squares

            void gorender (sf::RenderWindow* window,World* world,int hmap,int wmap);
    };

#endif // RENDER_H_INCLUDED
