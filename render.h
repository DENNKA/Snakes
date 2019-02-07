#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include "World.h"

    class render{
        public:
            void gorender (std::shared_ptr<sf::RenderWindow> window,World* world,int hmap,int wmap,int Size1,int Size2);
        private:
    };

#endif // RENDER_H_INCLUDED
