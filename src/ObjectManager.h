#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <vector>
#include "SFML/Graphics/Texture.hpp"
#include "gameObjects/Dino.h"
#include "gameObjects/Background.h"

class ObjMan{
    public:
        ObjMan(){
            std::srand(static_cast<unsigned int>(std::time(0)));
        }

        bool loadAll();

        sf::Sprite* getBackground();
        Dino* getDino();
        sf::Font* getFont();
        sf::Sprite* getRoadLines();

        void drawAll(sf::RenderWindow&);

        sf::Texture& getRandomTexture();


    private:
        std::vector<sf::Sprite*> objects;

        Dino _dino;
        sf::Texture _dinoTexture;

        Background _background;
        sf::Texture _backgroundTexture;
        
        sf::Texture _roadLinesTexture;
        sf::Sprite _roadLines;

        std::vector<sf::Texture> _obstacleTextures;

        bool loadObstacleTextures();

        sf::Font _font;


};
