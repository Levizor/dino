#include "Dino.h"
#include "SFML/Graphics/Rect.hpp"
#include "fmt/core.h"
#include <cmath>

const float JUMP_TIME= 0.6;
const float JUMP_HEIGHT = 100;
const float DEFAULT_HEIGHT = 500;


float parabola(float x){
    return JUMP_HEIGHT+(DEFAULT_HEIGHT-JUMP_HEIGHT)*std::pow((-2/JUMP_TIME)*x+1, 2);
}

Dino::Dino(){
    setPosition(100, DEFAULT_HEIGHT);
    setScale(0.7, 0.7);
}

void Dino::jump(){
    if(isJumping) return;

    isJumping=true;
    timeFromJump=0;
    
}

void Dino::update(const float& deltaTime){
    if(isJumping){
        timeFromJump+=deltaTime;
        float height = parabola(timeFromJump);
        if(height>DEFAULT_HEIGHT){
            height = DEFAULT_HEIGHT;
            isJumping=false;
        }

        setHeight(height);
    }

}

void Dino::setHeight(const float& y){
    setPosition(100, y);
}

sf::FloatRect Dino::getHitbox(){
    sf::FloatRect rect = getGlobalBounds();
    rect.left=rect.left+0.25*rect.width;
    rect.width=0.5*rect.width;
    rect.height=rect.height*0.6;

    return rect;
    
}
