#include "Buttonscntrl.h"


    void downtimedelay(Game *game){
        switch (game->gettimedelay()){
        //case 10: game->settimedelay(1); break;
        //case 1: game->settimedelay(0); break;
        default:game->settimedelay(game->gettimedelay()-10); break;
        }
    }

    void uptimedelay(Game *game){
        switch (game->gettimedelay()){
        //case 0: game->settimedelay(1); break;
        //case 1: game->settimedelay(10); break;
        default:game->settimedelay(game->gettimedelay()+10); break;
        }
    }

    void invert(bool &x){
        if(x){x=0;}else{x=1;}
    }

    void invertsimulation(Game *game){
        invert(game->simulation);
    }

    void invertrestart(Game *game){
        invert(game->restart);
    }

    void invertevolution(Game *game){
        invert(game->evolution);
    }

    void invertrandominbegin(Game *game){
        invert(game->randominbegin);
    }

    void invertrandommode(Game *game){
        invert(game->randommode);
    }

    void invertrendermap(Game *game){
        invert(game->rendermap);
    }

    void Buttonscntrl::update(int &i,Game *game,Snakescntrl *snakescntrl,World *world,bool mode){
        if (buttons[i].visible){
            buttons[i].switchcolor();

            switch (i) {
                case 0: uptimedelay(game); texts[11].setString(to_string(game->gettimedelay())); break;
                case 1: downtimedelay(game); texts[11].setString(to_string(game->gettimedelay())); break;
                case 2: invertsimulation(game); break;
                case 3: invertrestart(game); break;
                case 4: invertevolution(game);
                    buttons[5].invertvisible();     //if button doesn't pushed, next 2 buttons not visible
                    if(buttons[5].visible){
                        if(game->randominbegin)
                            buttons[6].invertvisible();
                    }else{buttons[6].visible=0;}
                break;
                case 5: invertrandominbegin(game);
                    if(game->randominbegin){buttons[6].visible=1;}else{buttons[6].visible=0;} break;    //if button doesn't pushed, next button not visible
                case 6: invertrandommode(game); break;
                case 7: game->setrandomx(game->getrandomx()+1); texts[5].setString(to_string(game->getrandomx())); break;
                case 8: game->setrandomx(game->getrandomx()-1); texts[5].setString(to_string(game->getrandomx())); break;
                case 9: game->foodpertick+=1+mode*19; texts[7].setString(to_string(game->foodpertick)); break;
                case 10: game->foodpertick-=1+mode*19; texts[7].setString(to_string(game->foodpertick)); break;
                case 11: snakescntrl->killall(); world->mapsetup(); break;
                case 12: invertrendermap(game); break;
                default: cerr<<"Error: button not found!"<<endl;
            }
        }
    }

    void Buttonscntrl::setuptexts(int Size,int Size2, int hmap, int wmap, int Size3/*=20*/){
        if (!font.loadFromFile("font/14219.ttf")) cerr<<"Error: font not found"<<endl;
        texts.push_back(sf::Text("Restartable",font,Size3));
        texts[0].setPosition(sf::Vector2f(35 + 4 * 15 + 3*64 ,5 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("Evolution",font,Size3));
        texts[1].setPosition(sf::Vector2f(35 + 4 * 15 + 3*64 ,5 + 33 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("random in begin",font,Size3-6));
        texts[2].setPosition(sf::Vector2f(35 + 5 * 15 + 5*64 ,5 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("relative random",font,Size3-6));
        texts[3].setPosition(sf::Vector2f(35 + 5 * 15 + 5*64 ,5 + 33 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("random x",font,Size3-6));
        texts[4].setPosition(sf::Vector2f(35 + 6 * 15 + 7*64 ,5 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("3",font,Size3));
        texts[5].setPosition(sf::Vector2f(35 + 6 * 15 + 7*64 ,5 + 33 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("food per tick",font,Size3-6));
        texts[6].setPosition(sf::Vector2f(35 + 7 * 15 + 9*64 ,5 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("1",font,Size3));
        texts[7].setPosition(sf::Vector2f(35 + 7 * 15 + 9*64 ,5 + 33 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("restarts:",font,Size3));
        texts[8].setPosition(sf::Vector2f(35 + 8 * 15 + 32 + 11*64 ,5 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("0",font,Size3));
        texts[9].setPosition(sf::Vector2f(35 + 8 * 15 + 32 + 11*64 ,5 + 33 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("delay (ms)",font,Size3));
        texts[10].setPosition(sf::Vector2f(35 + 15 , 5 + hmap * (Size+Size2)));
        texts.push_back(sf::Text("10",font,Size3));
        texts[11].setPosition(sf::Vector2f(35 + 15 , 5 + 33 +hmap * (Size+Size2)));

        #ifdef FPS
        texts.push_back(sf::Text("Fps",font,Size3));
        #endif // FPS
    }

    void Buttonscntrl::setupbuttons(int Size,int Size2, int hmap, int wmap){
        if (!texturebuttons.loadFromFile("img/buttons.png")) cerr<<"Error: texture file not found"<<endl;
        buttons.push_back(Button(texturebuttons,sf::Vector2f(15 , hmap * (Size+Size2)),sf::IntRect(31+3*64,0,32,32)));//increase speed
        buttons.push_back(Button(texturebuttons,sf::Vector2f(15 , 33 + hmap * (Size+Size2)),sf::IntRect(31+3*64,31,32,32)));//decrease speed
        buttons.push_back(Button(texturebuttons,sf::Vector2f(3 * 15 + 2*64 , hmap * (Size+Size2) ),sf::IntRect(2*64,0,64,64),1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(4 * 15 + 3*64 , hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(4 * 15 + 3*64 , 33 + hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(5 * 15 + 5*64 , hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(5 * 15 + 5*64 , 33 + hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),1));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(6 * 15 + 7*64 , hmap * (Size+Size2) ),sf::IntRect(31+3*64,0,32,32)));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(6 * 15 + 7*64 , 33 + hmap * (Size+Size2) ),sf::IntRect(31+3*64,31,32,32)));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(7 * 15 + 9*64 , hmap * (Size+Size2) ),sf::IntRect(31+3*64,0,32,32)));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(7 * 15 + 9*64 , 33 + hmap * (Size+Size2) ),sf::IntRect(31+3*64,31,32,32)));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(8 * 15 + 11*64 , hmap * (Size+Size2) ),sf::IntRect(4*64,0,64,64)));
        buttons.push_back(Button(texturebuttons,sf::Vector2f(10 * 15 + 13*64 , hmap * (Size+Size2) ),sf::IntRect(3*64,0,32,32),1));
        buttons[buttons.size()-1].switchcolor();
        buttons[5].visible=0;
        buttons[6].visible=0;
    }
