
#include "ObjectManager.h"
#include "Globals.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "fmt/core.h"


bool ObjMan::loadObstacleTextures(){
    for(int i=0; i<3; i++){
        sf::Texture texture;
        bool fine = texture.loadFromFile(TEXTURES[i]);
        if(!fine) return false;
        _obstacleTextures.push_back(texture);
    }
    return true;
}


bool ObjMan::loadAll(){
    bool fine = _backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);
    _background.setTexture(_backgroundTexture);

    fine = fine and _dinoTexture.loadFromFile(DINO_TEXTURE_PATH);
    _dino.setTexture(_dinoTexture);

    fine = fine and loadObstacleTextures();

    fine = fine and _font.loadFromFile(FONT_PATH);


    return fine;

}


sf::Sprite* ObjMan::getBackground(){
    return &_background;
}

Dino* ObjMan::getDino(){
    return &_dino;
}

std::vector<sf::Sprite*>* ObjMan::getObstacles(){
    return &_obstacles;
}

void ObjMan::drawAll(sf::RenderWindow& rw){
    rw.draw(_background);    
    rw.draw(_dino);
    for(sf::Sprite* obstacle: _obstacles){
        rw.draw(*obstacle);
    }
}

sf::Font* ObjMan::getFont(){
    return &_font;
}
