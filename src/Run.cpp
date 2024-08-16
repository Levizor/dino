#include "Run.h"
#include "Game.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "fmt/core.h"
#include <ctime>

float ACCELERATION = 0.25;

void Run::playLoop(const sf::Event& event){

    if(isGameOver()){
        _game.gameOver();
    }

    ObjMan& om = _game.om;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) or event.type == sf::Event::MouseButtonPressed){
        om.getDino()->jump();
    }

    float deltaTime = _clock.restart().asSeconds();
    time+=deltaTime;

    timeSinceSpeedIncrease+=deltaTime;
    if(timeSinceSpeedIncrease>5 and _speedModifier<15){
        timeSinceSpeedIncrease=0;
        _speedModifier+=1;
    }

    timeSinceLastObstacle+=deltaTime; 
    if(timeSinceLastObstacle>=1.2 and std::rand()%5==1){
        timeSinceLastObstacle=0;
        addObstacle();
    }

    om.getDino()->update(deltaTime);
    moveObstacles(deltaTime); 

    
    _game.clear();
    _game.draw();
    drawObstacles();
    _game.display();

}

void Run::gameOverLoop(const sf::Event& event){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        _game.play();
    } 
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
