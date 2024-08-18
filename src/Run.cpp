#include "Run.h"
#include "Game.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "fmt/core.h"
#include <cstdlib>
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
    _bestScore.setString(fmt::format("HI {:08}", _game.getBestScore()));

    _bestScore.setOrigin(_score.getGlobalBounds().width, 0);
    _bestScore.setPosition(_score.getGlobalBounds().left-150, 10);

    jump.setBuffer(_game.om.getJumpBuffer());
    jump.setVolume(4);
}

void Run::playLoop(const sf::Event& event){

    if(isGameOver()){
        _game.setState(GameOver);
        _game.om.getDino()->setOverTexture();
        if(score>_game.getBestScore()){
            _game.setBestScore(score);
            _bestScore.setString(fmt::format("HI: {:08}", _game.getBestScore()));
        }
        return;
    }

    ObjMan& om = _game.om;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) or event.type == sf::Event::MouseButtonPressed){
        if(!om.getDino()->isJumping){
            om.getDino()->jump();
            jump.play();
        }
    }

    float deltaTime = _clock.restart().asSeconds();
    time+=deltaTime;
    score=time*_speedModifier;

    timeSinceSpeedIncrease+=deltaTime;
    if(timeSinceSpeedIncrease>3 and _speedModifier<20){
        timeSinceSpeedIncrease=0;
        _speedModifier+=1;
    }

    timeSinceLastObstacle+=deltaTime; 
    if(timeSinceLastObstacle>=1){
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
    _game.om.getDino()->setDefaultTexture();
    _game.om.getDino()->jump();
    _game.om.getDino()->update(1);

    for(sf::Sprite* ob: _obstacles){
        delete ob;
    }
    _obstacles.erase(_obstacles.begin(), _obstacles.end());
    _speedModifier=8;
    time=0;
    timeSinceSpeedIncrease=0;
    timeSinceLastObstacle=0;
    x=1600;
}

void Run::addObstacle(){
    if(!_obstacles.empty())
        x = _obstacles.back()->getPosition().x;

    int posx = x+1100+std::rand()%1000;
    if(posx<=1800){
        posx=2000;
    }

    if(_speedModifier>12 and std::rand()%3==0){
        

        int c=2;
        if(_speedModifier>18){
            c+=std::rand()%2;
        }


        for(int i=0; i<c; i++){
            sf::Sprite* o = new sf::Sprite();
            o->setTexture(_game.om.getRandomTexture());
            o->setScale(0.7, 0.7);
            o->setOrigin((o->getGlobalBounds()).width, o->getGlobalBounds().height);
            posx+=o->getGlobalBounds().width+20;
            o->setPosition(posx, 660);
            _obstacles.push_back(o);
        }


    }else if(_speedModifier>16 and std::rand()%3==0){
        sf::Sprite* pit = new sf::Sprite();        

        pit->setTexture(_game.om.getPitTexture());
        pit->setScale(0.7, 0.7);
        pit->setOrigin(pit->getGlobalBounds().width, pit->getGlobalBounds().height);
        pit->setPosition(posx, 720);
        _obstacles.push_back(pit);


    }else if(_speedModifier>10 and std::rand()%3==1){
        Object* drone = new Object();

        drone->setTextures(_game.om.getDroneTextures());
        drone->setScale(2.4, 2.4);
        drone->setOrigin(drone->getGlobalBounds().width, drone->getGlobalBounds().height);

        if(std::rand()%2==1){
            drone->setPosition(posx, 450);
        }else{
            drone->setPosition(posx, 800);
        }
        _obstacles.push_back(drone);
    }else{
        sf::Sprite* o = new sf::Sprite();    
        o->setTexture(_game.om.getRandomTexture());
        o->setScale(0.7, 0.7);
        o->setOrigin((o->getGlobalBounds()).width, o->getGlobalBounds().height);
        o->setPosition(posx, 660);

        _obstacles.push_back(o);
    }



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
        if(Object* o = dynamic_cast<Object*>(ob)){
            o->animate(deltaTime);
        }
        
    }

    if(_game.om.getBackground()->getPosition().x<-3200){
        _game.om.getBackground()->setPosition(0, 0);
    }
    _game.om.getBackground()->move(-0.1*_speedModifier, 0);

    _game.om.getRoad()->move(-100*_speedModifier*deltaTime, 0);
    if(_game.om.getRoad()->getPosition().x<=-4800){
        _game.om.getRoad()->setPosition(0, 0);
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
            if(Object* o = dynamic_cast<Object*>(ob)){
                o->setOverTexture();
            }
            return true;

        }
    }
    return false;
}

void Run::drawScores(){
    _game.rw.draw(_score);
    _game.rw.draw(_bestScore);
}
