#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include "World.h"

    class Render{
        public:
            void gorender (sf::RenderWindow* window,World* world,int hmap,int wmap,int Size1,int Size2);
        private:
    };

#endif // RENDER_H_INCLUDED
