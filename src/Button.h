#pragma once

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include <string>

class Button:public sf::Drawable{
    public:
        Button();
        Button(std::string string, bool toggle=false);

        void setText(std::string text);
        bool isPressed();
        void update(const sf::Event& e, sf::RenderWindow& rw);
        void setFont(const sf::Font& font);
        
        void setFontSize(const int& size);
        void setTextColor(const sf::Color& color);
        void setBackgroundColor(sf::Color color);
        void setPosition(sf::Vector2f position);
        void setPosition(float x, float y);
        void setSize(const int& width, const int& height);

        sf::Text* getText();

    private:
        bool _toggle = false;

        bool _mouseInButton;
        bool _isPressed = false;

        sf::RectangleShape _shape;

        sf::Text _text;

        sf::Color c_normal;
        sf::Color c_pressed;
        sf::Color c_hovered;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
