#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <vector>

class Object: public sf::Sprite{
    public:
        void animate(const float& deltaTime);
        void setTextures(std::vector<sf::Texture*>* textures);
        void setFrameRate(const float& timePerFrame);


        void setOverTexture();
        void setDefaultTexture();

        std::vector<sf::Texture*>* _textures;
        float _timePerFrame;
        float counter=0;
        int index=0;

};
