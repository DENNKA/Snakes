#include "render.h"
#include <string>

using namespace sf;
        render::render(sf::RenderWindow* win) : window(win){}
        void render::gorender (std::string *Map,short hmap,short wmap,short Size,short Size2){
            window->clear();
            RectangleShape rectangle(Vector2f(Size, Size));

            for (int i = 0; i < hmap; i++){
                for (int j = 0; j < wmap; j++){
                if (Map[i][j] == ' ')  rectangle.setFillColor(sf::Color(0, 0, 0));
                if (Map[i][j] == 's')  rectangle.setFillColor(sf::Color(0, 250, 0));
                if (Map[i][j] == '0')  rectangle.setFillColor(sf::Color(150, 0, 0));
                if (Map[i][j] == 'f')  rectangle.setFillColor(sf::Color(150, 150, 150));

                rectangle.setPosition(j * (Size+Size2), i * (Size+Size2));
                window->draw(rectangle);
                }
            }

            window->display();
        }
