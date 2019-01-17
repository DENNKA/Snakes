#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>

    class render{
        public:
            render(sf::RenderWindow* win);
            void gorender (std::string *Map,short hmap,short wmap,short Size1,short Size2);
        private:
            std::unique_ptr<sf::RenderWindow> window;
    };

#endif // RENDER_H_INCLUDED
