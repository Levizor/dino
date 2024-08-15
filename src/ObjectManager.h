#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <string>
#include <vector>
#include "SFML/Graphics/Texture.hpp"
#include "gameObjects/Dino.h"
#include "gameObjects/Background.h"

class ObjMan{
    public:

        bool loadAll();

        sf::Sprite* getBackground();
        Dino* getDino();
        std::vector<sf::Sprite*>* getObstacles();
        sf::Font* getFont();

        void drawAll(sf::RenderWindow&);


    private:
        std::vector<sf::Sprite*> objects;

        Dino _dino;
        sf::Texture _dinoTexture;

        Background _background;
        sf::Texture _backgroundTexture;

        std::vector<sf::Texture> _obstacleTextures;
        std::vector<sf::Sprite*> _obstacles;

        bool loadObstacleTextures();

        sf::Font _font;


};
