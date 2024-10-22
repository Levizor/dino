#include "Game.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Window/Event.hpp"
#include "fmt/core.h"
#include <fstream>
#include <string>
#include "Score.h"

float aspectRatio = 16./9;





void Game::init(){

    bool fine = om.loadAll();

    _bestScore = sc::readBestScore();

    rw.create(
            sf::VideoMode(
                1600, 900, 32),
            "Dino");
    rw.setFramerateLimit(60);
    rw.setKeyRepeatEnabled(false);

    _menu.init();
    _run.init();

    gameOver.setBuffer(om.getGameOverBuffer());

    view = sf::View(sf::FloatRect(0, 0, 1600, 900));
    rw.setView(view);

    rw.display();
    rw.requestFocus();

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
                _menu.gameOverLoop(event);
                break;

        }
    }
}

bool Game::isExiting(){
    return _state==State::Exiting;
}

void Game::clear(){
    rw.clear(sf::Color(0xDBDBDBFF));
}

void Game::draw(){
    om.drawAll(rw);
    _run.drawObstacles();
}

void Game::display(){
    rw.display();
}

void Game::setState(const State& state){

    switch(state){
        case Playing:
            _run.restart();
            break;
        case InMenu:
            _menu.updateScore();
            _run.restart();
        break;
        case GameOver:
            gameOver.play(); 
            break;

    }
    _state = state;
}

int Game::getBestScore(){
    return _bestScore;
}

void Game::setBestScore(const int& score){
    _bestScore = score;
    sc::writeBestScore(score); 
}
