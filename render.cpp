#include "render.h"
#include <string>

using namespace sf;
        render::render(sf::RenderWindow* win) : window(win){}
        void render::gorender (std::string *Map,short hmap,short wmap,short Size,short Size2){
            window->clear();
            RectangleShape rectangle(Vector2f(Size, Size));

            for (int i = 0; i < hmap; i++){
                for (int j = 0; j < wmap; j++){
                    switch (Map[i][j]){
                        case ' ':  rectangle.setFillColor(sf::Color(0, 0, 0));break;
                        case 's':  rectangle.setFillColor(sf::Color(0, 250, 0));break;
                        case '0':  rectangle.setFillColor(sf::Color(150, 0, 0));break;
                        case 'f':  rectangle.setFillColor(sf::Color(150, 150, 150));break;
                        case 'd':  rectangle.setFillColor(sf::Color(250, 250, 100));break;
                    }

                rectangle.setPosition(j * (Size+Size2), i * (Size+Size2));
                window->draw(rectangle);
                }
            }

            window->display();
        }
