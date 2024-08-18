
#include "ObjectManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "fmt/core.h"
#include <cstdlib>
#include <vector>
#include "assets.h"



bool ObjMan::loadDinoTextures(){
    bool fine = true;

    for(int i=0; i<6; i++){
        sf::Texture* t = new sf::Texture();
        fine = fine and t->loadFromMemory(dinopng[i], dino_size[i]);
        _dinoTextures.push_back(t);
    }

    return fine;
}

bool ObjMan::loadDroneTextures(){
    bool fine = true;

    for(int i=0; i<3; i++){
        sf::Texture* t = new sf::Texture();
        fine = fine and t->loadFromMemory(dronepng[i], *drone_size[i]);
        _droneTextures.push_back(t);
    }

    return fine;

}

bool ObjMan::loadObstacleTextures(){
        
    bool fine = true;
    for(int i=0; i<3; i++){
        sf::Texture texture;
        fine = fine and texture.loadFromMemory(obstaclepng[i], *obstacle_size[i]);
        _obstacleTextures.push_back(texture);
    }
    fine = fine and _pitTexture.loadFromMemory(pit_png, pit_png_size);

    return fine;
}

sf::Texture& ObjMan::getRandomTexture(){
    int rand = std::rand()%3;
    return _obstacleTextures.at(rand);
}

sf::Texture& ObjMan::getPitTexture(){
    return _pitTexture;
}


bool ObjMan::loadAll(){
    bool fine = _backgroundTexture.loadFromMemory(background_png, background_png_size);

    fine = fine and loadDinoTextures();

    fine = fine and _roadTexture.loadFromMemory(road_png, road_png_size);

    fine = fine and loadObstacleTextures();

    fine = fine and _font.loadFromMemory(ARCADECLASSIC_TTF, ARCADECLASSIC_TTF_size);

    fine = fine and loadDroneTextures();

    fine = fine and _gameOverBuffer.loadFromMemory(gameover_mp3, gameover_mp3_size);


    fine = fine and _jumpBuffer.loadFromMemory(jump_wav, jump_wav_size);

    if(fine){
        _dino.setTextures(&_dinoTextures);
        _dino.setFrameRate(0.2);
        _background.setTexture(_backgroundTexture);
        _road.setTexture(_roadTexture);
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
    rw.draw(_road);
    rw.draw(_dino);
}

sf::Font* ObjMan::getFont(){
    return &_font;
}

sf::Sprite* ObjMan::getRoad(){
    return &_road;
}

std::vector<sf::Texture*>* ObjMan::getDroneTextures(){
    return &_droneTextures;
}
