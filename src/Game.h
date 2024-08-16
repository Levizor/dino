#pragma once


#include "Menu.h"
#include "Run.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "ObjectManager.h"


class Game{

    public:
        Game():_menu(*this), _run(*this){};
        ObjMan om;

        sf::RenderWindow rw; 
        void clear();
        sf::Vector2u resoultion;
        void draw();


        void init();
        void start();
        void play();
        void gameOver();
        void quit();
        void display();
        bool isExiting();



    private:
        enum State{
            Exiting, Playing, InMenu, GameOver
        };

        sf::View view;

        State _state;

        Menu _menu;
        Run _run;


};


