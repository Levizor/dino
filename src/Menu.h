#pragma once

#include "Button.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include <vector>

class Game;

class Menu{
    public:
        Menu();
        Menu(Game& game):_game(game){};

        void position();

        void loop(const sf::Event& event);
        void gameOverLoop(const sf::Event& event);
        void updateScore();

        void init();
    private:
        void draw();
        Game& _game;
        Button _playButton;
        Button _quitButton;
        Button _repeatButton;
        Button _MenuButton;
        sf::Text _label;
        sf::Text _bsLabel;
        
        std::vector<Button*> _menuButtons;
        std::vector<Button*> _gameOverButtons;
};
