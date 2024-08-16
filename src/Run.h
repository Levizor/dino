#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include <queue>
#include <vector>

class Game;

class Run{
    public:
        Run();
        Run(Game& game):_game(game){};

        void playLoop(const sf::Event& event);
        void gameOverLoop(const sf::Event& event);
        void restart();


    private:
        bool isGameOver();
        void saveResult();
        void addObstacle();
        void drawObstacles();
        void moveObstacles(const float& deltaTime);

        Game& _game;
        sf::Clock _clock; 
        std::deque<sf::Sprite*> _obstacles;

        float _speedModifier=8;

        float time=0;
        float timeSinceSpeedIncrease=0;
        float timeSinceLastObstacle = 0;

};
