
#include "ObjectManager.h"
#include "Globals.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "fmt/core.h"
#include <cstdlib>

bool ObjMan::loadObstacleTextures(){
    for(int i=0; i<3; i++){
        sf::Texture texture;
        bool fine = texture.loadFromFile(TEXTURES[i]);
        if(!fine) return false;
        _obstacleTextures.push_back(texture);
    }
    return true;
}

sf::Texture& ObjMan::getRandomTexture(){
    int rand = std::rand()%3;
    return _obstacleTextures.at(rand);
}


bool ObjMan::loadAll(){
    bool fine = _backgroundTexture.loadFromFile(BACKGROUND_IMAGE_PATH);

    fine = fine and _dinoTexture.loadFromFile(DINO_TEXTURE_PATH);

    fine = fine and _roadLinesTexture.loadFromFile(ROAD_LINES_TEXTURE_PATH);

    fine = fine and loadObstacleTextures();

    fine = fine and _font.loadFromFile(FONT_PATH);

    if(fine){
        _dino.setTexture(_dinoTexture);
        _background.setTexture(_backgroundTexture);
        _roadLines.setTexture(_roadLinesTexture);
    }



    return fine;

}


sf::Sprite* ObjMan::getBackground(){
    return &_background;
}

Dino* ObjMan::getDino(){
    return &_dino;
}


void ObjMan::drawAll(sf::RenderWindow& rw){
    rw.draw(_background);    
    rw.draw(_roadLines);
    rw.draw(_dino);
}

sf::Font* ObjMan::getFont(){
    return &_font;
}

sf::Sprite* ObjMan::getRoadLines(){
    return &_roadLines;
}
