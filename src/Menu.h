#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

class Menu{
    public:
        Menu(){};
        Menu(sf::RenderWindow* rw):rw(rw){};
        void loop();
    private:
        sf::RenderWindow* rw;
};
