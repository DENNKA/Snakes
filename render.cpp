#include "render.h"
#include <string>

using namespace sf;

        void Render::rendersetup(sf::RenderWindow* swindow,World* sworld,Buttonscntrl *sbuttonscntrl,Game* sgame,Snakescntrl* ssnakescntrl,int shmap,int swmap){
            window=swindow;
            world=sworld;
            buttonscntrl=sbuttonscntrl;
            snakescntrl=ssnakescntrl;
            game=sgame;
            hmap=shmap;
            wmap=swmap;
            setsizes(Size,Size2);
        }

        void Render::setsizes(int sSize,int sSize2){
            Size=sSize;
            Size2=sSize2;
            Size3=Size+Size2;
            glPointSize(Size);
        }

        void Render::rendermap (){
            glBegin(GL_POINTS);
            /*int mode=1;
            if(mode){
                int ssize=snakescntrl->snakes.size();
                for(int i=0;i<ssize;i++){
                    glVertex2f((snakescntrl->snakes[i].getx() * Size3 + Size/2),(snakescntrl->snakes[i].gety() * Size3 + Size/2));
                    for (int i=0;i<7;i++){
                        for (int j=0;j<7;j++){
                            if ((snakescntrl->snakes[i].gety()-3+i)>=0&&(snakescntrl->snakes[i].getx()-3+j)>=0){
                                if ((snakescntrl->snakes[i].gety()-3+i)<world->hmap&&(snakescntrl->snakes[i].getx()-3+j)<world->wmap){
                                    switch (world->getmap(snakescntrl->snakes[i].gety()-3+i,snakescntrl->snakes[i].getx()-3+j)){
                                        case ' ': glColor3f(0.1,0.1,0.1); break;
                                        case 's': glColor3f(0,0.9,0); break;
                                        case '0': glColor3f(0.9,0,0); break;
                                        case 'f': glColor3f(0.7,0.7,0.7); break;
                                        case 'd': glColor3f(0.94,0.94,0.4); break;
                                    }
                                    std::cout<<world->getmap(snakescntrl->snakes[i].gety()-3+i,snakescntrl->snakes[i].getx()-3+j);
                                    //std::cout<<snakescntrl->snakes[i].gety()-3+i * Size3<<std::endl;
                                    glVertex2f((snakescntrl->snakes[i].getx()-3+j * Size3 + Size/2),(snakescntrl->snakes[i].gety()-3+i * Size3 + Size/2));
                                }
                            }
                        }
                        std::cout<<std::endl;
                    }
                }
            }*/
            for (int i = 0; i < hmap; i++){
                for (int j = 0; j < wmap; j++){
                    switch (world->getmap(i,j)){
                        case ' ': continue;
                        case 's': glColor3f(0,0.9,0); break;
                        case '0': glColor3f(0.9,0,0); break;
                        case 'f': glColor3f(0.7,0.7,0.7); break;
                        case 'd': glColor3f(0.94,0.94,0.4); break;
                    }
                    glVertex2f(j * Size3 + Size/2,i * Size3 + Size/2);
                }
            }
            glEnd();
        }

        void Render::renderbuttonsandtexts(){
            int bsize=(int)buttonscntrl->buttons.size();
            for(int i=0;i<bsize;i++){
                if(buttonscntrl->buttons[i].visible)
                    window->draw(buttonscntrl->buttons[i].sprite);
            }
            int tsize=(int)buttonscntrl->texts.size();
            for(int i=0;i<tsize;i++){
                if(i==2&&buttonscntrl->buttons[5].visible==0) continue;
                if(i==3&&buttonscntrl->buttons[6].visible==0) continue;
                window->draw(buttonscntrl->texts[i]);
            }
        }
