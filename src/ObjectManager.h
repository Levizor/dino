#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <vector>
#include "SFML/Graphics/Texture.hpp"
#include "Dino.h"

class ObjMan{
    public:
        ObjMan(){
            std::srand(static_cast<unsigned int>(std::time(0)));
        }

        bool loadAll();

        sf::Sprite* getBackground();
        Dino* getDino();
        sf::Font* getFont();
        sf::Sprite* getRoad();

        void drawAll(sf::RenderWindow&);

        sf::Texture& getRandomTexture();
        sf::Texture& getPitTexture();

        std::vector<sf::Texture*>* getDroneTextures();

        sf::SoundBuffer& getGameOverBuffer(){
            return _gameOverBuffer;
        }

        sf::SoundBuffer& getJumpBuffer(){
            return _jumpBuffer;
        }
        
    private:
        std::vector<sf::Sprite*> objects;

        Dino _dino;
        sf::Texture _dinoTexture;
        std::vector<sf::Texture*> _dinoTextures;
        std::vector<sf::Texture*> _droneTextures;

        Object _background;
        sf::Texture _backgroundTexture;
        
        sf::Texture _roadTexture;
        Object _road;


        sf::Texture _pitTexture;

        std::vector<sf::Texture> _obstacleTextures;

        sf::SoundBuffer _gameOverBuffer;
        sf::SoundBuffer _jumpBuffer;

        bool loadDinoTextures();

        bool loadDroneTextures();

        bool loadObstacleTextures();

        sf::Font _font;


};
