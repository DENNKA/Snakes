#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>

    class render{
        public:
            void gorender (std::shared_ptr<sf::RenderWindow> window,std::string *Map,short hmap,short wmap,short Size1,short Size2);
        private:
    };

#endif // RENDER_H_INCLUDED
