#include "Game.h"
#include "SFML/Window/Event.hpp"
#include "fmt/core.h"


void Game::init(){

    _rw.create(
        sf::VideoMode(
            1920, 1080, 32),
        "Dino Game");
    _rw.setFramerateLimit(30);
    _rw.setVerticalSyncEnabled(true);
    _rw.setKeyRepeatEnabled(false);
    _rw.display();
    _rw.requestFocus();

}

void Game::start(){
    _state = InMenu;

    sf::Event event;
    while(!isExiting()){
        while(_rw.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    _state = Exiting;
                    break;
                case sf::Event::Resized:
                    _resoultion = _rw.getSize();
                    break;
            }

        }

        switch (_state){
            case Exiting:
                _rw.close();
                return;
            case InMenu:
                _menu.loop();
                break;
            case Playing:
                loop();
        }
    }
}

bool Game::isExiting(){
    return _state==State::Exiting;
}

void Game::loop(){

}
