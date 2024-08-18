#pragma once


#include "Menu.h"
#include "Run.h"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "ObjectManager.h"

enum State{
    Exiting, Playing, InMenu, GameOver
};

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
        void display();
        bool isExiting();

        void setState(const State& state);

        int getBestScore();
        void setBestScore(const int& score);


        Menu _menu;
        Run _run;

    private:

            sf::View view;

            State _state;

            sf::Sound gameOver;


            int _bestScore;


};


