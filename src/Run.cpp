#include "Run.h"
#include "Game.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "fmt/core.h"
#include <ctime>
#include "Score.h"

float ACCELERATION = 0.25;

void Run::init(){
    _score.setFont(*_game.om.getFont());
    _score.setFillColor(sf::Color(0xf7b801ff));
    _score.setCharacterSize(50);
    _score.setString("00000000");

    sf::Vector2u ws = _game.rw.getSize();
    _score.setOrigin(_score.getGlobalBounds().width, 0);
    _score.setPosition(ws.x-10, 10);

    _bestScore.setFont(*_game.om.getFont());
    _bestScore.setFillColor(sf::Color(0xf7b801ff));
    _bestScore.setCharacterSize(50);
    _bestScore.setString(fmt::format("HI: {:08}", _game.getBestScore()));

    _bestScore.setOrigin(_score.getGlobalBounds().width, 0);
    _bestScore.setPosition(_score.getGlobalBounds().left-150, 10);
}

void Run::playLoop(const sf::Event& event){

    if(isGameOver()){
        _game.setState(GameOver);
        if(score>_game.getBestScore()){
            _game.setBestScore(score);
            _bestScore.setString(fmt::format("HI: {:08}", _game.getBestScore()));
        }
        return;
    }

    ObjMan& om = _game.om;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) or event.type == sf::Event::MouseButtonPressed){
        om.getDino()->jump();
    }

    float deltaTime = _clock.restart().asSeconds();
    time+=deltaTime;
    score=time*_speedModifier;

    timeSinceSpeedIncrease+=deltaTime;
    if(timeSinceSpeedIncrease>3 and _speedModifier<30){
        timeSinceSpeedIncrease=0;
        _speedModifier+=1;
    }

    timeSinceLastObstacle+=deltaTime; 
    if(timeSinceLastObstacle>=1.5 and std::rand()%5==1){
        timeSinceLastObstacle=0;
        addObstacle();
    }

    om.getDino()->update(deltaTime);
    moveObstacles(deltaTime); 

    _score.setString(fmt::format("{:08}", score));

    
    _game.clear();
    _game.draw();
    drawScores();
    _game.display();
}

void Run::restart(){
    _clock.restart();
    _game.om.getDino()->jump();
    for(sf::Sprite* ob: _obstacles){
        delete ob;
    }
    _obstacles.erase(_obstacles.begin(), _obstacles.end());
    _speedModifier=8;
    time=0;
    timeSinceSpeedIncrease=0;
    timeSinceLastObstacle=0;
}

void Run::addObstacle(){
    sf::Sprite* o = new sf::Sprite();    
    o->setTexture(_game.om.getRandomTexture());
    o->setScale(0.7, 0.7);
    o->setPosition(2000+std::rand()%800, 700);
    o->setOrigin((o->getTextureRect()).width, o->getTextureRect().height);

    _obstacles.push_back(o);


}

void Run::moveObstacles(const float& deltaTime){
    if(_obstacles.size()>0){
        if(_obstacles[0]->getPosition().x<-50){
            delete _obstacles[0];
            _obstacles.pop_front(); 
        }
    }
    for(sf::Sprite* ob:_obstacles){
        ob->move(-100*_speedModifier*deltaTime, 0);
    }

    _game.om.getRoadLines()->move(-100*_speedModifier*deltaTime, 0);
    if(_game.om.getRoadLines()->getPosition().x<=-1600){
        _game.om.getRoadLines()->setPosition(0, 0);
    }
}

void Run::drawObstacles(){
    for(sf::Sprite* ob:_obstacles){
        _game.rw.draw(*ob);
    }
}

bool Run::isGameOver(){
    Dino * dino = _game.om.getDino();
    for(sf::Sprite* ob: _obstacles){
        if(dino->getHitbox().intersects(ob->getGlobalBounds())){
            return true;
        }
    }
    return false;
}

void Run::drawScores(){
    _game.rw.draw(_score);
    _game.rw.draw(_bestScore);
}
