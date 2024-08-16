#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
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
        void restart();
        void drawObstacles();
        void drawScores();
        void init();


    private:
        bool isGameOver();
        void saveResult();
        void addObstacle();
        void moveObstacles(const float& deltaTime);

        Game& _game;
        sf::Clock _clock; 
        std::deque<sf::Sprite*> _obstacles;
        sf::Text _score;
        sf::Text _bestScore;

        float _speedModifier=8;

        float time=0;
        int score=0;
        float timeSinceSpeedIncrease=0;
        float timeSinceLastObstacle = 1;

};
