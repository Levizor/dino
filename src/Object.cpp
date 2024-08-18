#include "Object.h"
#include "SFML/Graphics/Texture.hpp"
#include "fmt/core.h"

void Object::animate(const float& deltaTime){
    counter+=deltaTime;
    if(counter>=_timePerFrame){
        counter=0;
        index=(index+1)%(_textures->size()-1);
        setTexture(*_textures->at(index));
    }
}

void Object::setTextures(std::vector<sf::Texture*>* textures){
    _textures=textures;
    setTexture(*_textures->at(0));
}

void Object::setFrameRate(const float& frate){
    _timePerFrame=frate;
}

void Object::setOverTexture(){
    setTexture(*_textures->at(_textures->size()-1), true);
    
}

void Object::setDefaultTexture(){
    setTexture(*_textures->at(0));
}
