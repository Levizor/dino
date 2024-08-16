#include "Button.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include <iostream>

Button::Button(){
    setText("Button");
    setFontSize(30);

    _shape = sf::RectangleShape(sf::Vector2f(100, 60));
    _shape.setFillColor(c_normal);
    setBackgroundColor(sf::Color(0xf7b801ff));

    sf::Vector2f pos = _shape.getPosition();
    _text.setPosition(pos.x+_shape.getSize().x/2, pos.y+_shape.getSize().y/2);
    _text.setFillColor(sf::Color(0x008080ff));

}

Button::Button(std::string text, bool toggle):Button(){
    setText(text);
    _toggle = toggle;
}

void Button::setText(std::string text){
    _text.setString(text);
}

bool Button::isPressed(){
    bool p=_isPressed;
    _isPressed=false;
    return p;
}
void Button::update(const sf::Event& e, sf::RenderWindow& rw){
    sf::Vector2i mousePos = sf::Mouse::getPosition(rw);
    mousePos = (sf::Vector2i)rw.mapPixelToCoords(mousePos);
    _mouseInButton = _shape.getGlobalBounds().contains(mousePos.x, mousePos.y);

    if(_mouseInButton){
        if(e.type == sf::Event::MouseButtonPressed){
            _isPressed = true;
            _shape.setFillColor(c_pressed);
        }
        _shape.setFillColor(c_hovered);
    }else{
        _shape.setFillColor(c_normal);
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_shape, states);
    target.draw(_text, states);
}

void Button::setFont(const sf::Font& font){
    _text.setFont(font);
}

void Button::setFontSize(const int& size){
    _text.setCharacterSize(size); 
}

void Button::setTextColor(const sf::Color& color){
    _text.setFillColor(color);
}

sf::Text* Button::getText(){
    return &_text;
}

void Button::setBackgroundColor(sf::Color color){
    c_normal=color;
    c_hovered = sf::Color(c_normal.toInteger()-0x101010);
    c_pressed = sf::Color(c_normal.toInteger()-0x202020);
}

void Button::setPosition(sf::Vector2f position){
    _shape.setPosition(position);
    // _text.setOrigin(_text.getGlobalBounds().getSize() / 2.f + _text.getLocalBounds().getPosition());
    sf::Rect textRect = _text.getGlobalBounds();
    int x = position.x + (_shape.getSize().x - textRect.width)/2;
    int y = position.y + (_shape.getSize().y - textRect.height)/2;
    _text.setPosition(x, y);

}
void Button::setPosition(float x, float y){
    setPosition(sf::Vector2f(x, y));
}

void Button::setSize(const int& width, const int& height){
    _shape.setSize(sf::Vector2f(width, height));
}
