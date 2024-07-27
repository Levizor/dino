#pragma once


#include "Menu.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Game{

    public:
        void init();
        void start();

        bool isExiting();

    private:
        sf::RenderWindow _rw; 
        enum State{
            Exiting, Playing, InMenu
        };

        State _state;

        sf::Vector2u _resoultion;

        void loop();
    
        Menu _menu;

};
