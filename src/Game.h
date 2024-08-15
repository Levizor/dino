#pragma once


#include "Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "ObjectManager.h"


class Game{

    public:
        Game():_menu((*this)){};

        sf::RenderWindow rw; 
        void clear();
        sf::Vector2u resoultion;
        ObjMan om;
        void draw();


        void init();
        void start();
        void play();
        void quit();
        bool isExiting();



    private:
        enum State{
            Exiting, Playing, InMenu
        };

        sf::View view;

        State _state;

        void playLoop(const sf::Event& event);
    
        Menu _menu;

        sf::Clock clock; 

};


