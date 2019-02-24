#include "render.h"
#include <string>

using namespace sf;

        void Render::render (RenderWindow* window,World* world,int hmap,int wmap){

            RectangleShape rectangle(Vector2f(Size, Size));

            for (int i = 0; i < hmap; i++){
                for (int j = 0; j < wmap; j++){
                    if(world->getmap(i,j)==' '){continue;}else{
                        switch (world->getmap(i,j)){
                            case 's':  rectangle.setFillColor(sf::Color(0, 250, 0)); break;
                            case '0':  rectangle.setFillColor(sf::Color(150, 0, 0)); break;
                            case 'f':  rectangle.setFillColor(sf::Color(150, 150, 150)); break;
                            case 'd':  rectangle.setFillColor(sf::Color(250, 250, 100)); break;
                        }   // nado izmenit
                        rectangle.setPosition(j * (Size+Size2), i * (Size+Size2));
                        window->draw(rectangle);
                    }
                }
            }
        }

        void Render::renderbuttonsandtexts(RenderWindow* window,Buttonscntrl *buttonscntrl){
            for(int i=0;i<(int)buttonscntrl->buttons.size();i++){
                if(buttonscntrl->buttons[i].visible)
                    window->draw(buttonscntrl->buttons[i].sprite);
            }
            for(int i=0;i<(int)buttonscntrl->texts.size();i++){
                if(i==2&&buttonscntrl->buttons[5].visible==0) continue;
                if(i==3&&buttonscntrl->buttons[6].visible==0) continue;
                window->draw(buttonscntrl->texts[i]);
            }
        }
