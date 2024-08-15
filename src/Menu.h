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

        void init();
    private:
        void draw();
        Game& _game;
        Button _playButton;
        Button _quitButton;
        sf::Text _label;
        
        std::vector<Button*> _buttons;
};
