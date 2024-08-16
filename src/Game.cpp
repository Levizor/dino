#include "Game.h"
#include "Globals.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include "fmt/core.h"

float aspectRatio = 16./9;


void Game::init(){

    rw.create(
        sf::VideoMode(
            1600, 900, 32),
        "Dino");
    rw.setFramerateLimit(60);
    rw.setKeyRepeatEnabled(false);

    _menu.init();

    view = sf::View(sf::FloatRect(0, 0, 1600, 900));
    rw.setView(view);


    rw.display();
    rw.requestFocus();
    bool fine = om.loadAll();
    fmt::println("Loaded fine {}", fine);
    

}

void Game::start(){
    _state = InMenu;

    sf::Event event;
    while(!isExiting()){
        while(rw.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    _state = Exiting;
                    break;
                case sf::Event::Resized:
                    float newWidth, newHeight;
                    if((.0+event.size.width)/event.size.height>aspectRatio){
                        newWidth = event.size.height*aspectRatio;
                        float a = (event.size.width - newWidth)/2/event.size.width;
                        view.setViewport(sf::FloatRect(a, 0, 1-2*a, 1));
                    }else{
                        newHeight = event.size.width/aspectRatio;
                        float a = (event.size.height - newHeight)/2/event.size.height;
                        view.setViewport(sf::FloatRect(0, a, 1, 1-2*a));
                    }
                    rw.setView(view);
                    break;
            }

        }

        switch (_state){
            case Exiting:
                rw.close();
                return;
            case InMenu:
                _menu.loop(event);
                break;
            case Playing:
                _run.playLoop(event);
                break;
            case GameOver:
                _run.gameOverLoop(event);
                break;

        }
    }
}

bool Game::isExiting(){
    return _state==State::Exiting;
}

void Game::clear(){
    rw.clear(BACKGROUND_COLOR);
}

void Game::draw(){
    om.drawAll(rw);
}

void Game::display(){
    rw.display();
}

void Game::quit(){
    _state = Exiting;
}

void Game::play(){
    _state = Playing;
    _run.restart();
}

void Game::gameOver(){
    _state = GameOver;
}
