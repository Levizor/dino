#include "Menu.h"
#include "Button.h"
#include "SFML/System/Vector2.hpp"
#include "Game.h"
#include "fmt/core.h"


void Menu::init(){
    _playButton = Button("Play");
    _quitButton = Button("Quit");
    _buttons.push_back(&_playButton);
    _buttons.push_back(&_quitButton);


    int gap = 120;
    sf::Vector2u ws = _game.rw.getSize();
    fmt::println("{}, {}", ws.x, ws.y);
    sf::Vector2f lastPos = sf::Vector2f(ws.x-250, ws.y/2.);
    fmt::println("{}, {}", lastPos.x, lastPos.y);

    
    for(Button* button: _buttons){
        button->setPosition(lastPos.x, lastPos.y);
        button->setFont(*_game.om.getFont());
        button->setSize(200, 100);
        lastPos.y = lastPos.y + gap;
    }

    _label.setFont(*_game.om.getFont());
    _label.setFillColor(sf::Color(0x12664fff));
    _label.setCharacterSize(200);
    _label.setString("Dino");
    _label.setOrigin(_label.getGlobalBounds().width, 0);
    _label.setPosition(ws.x-560, ws.y/2.-300);
}

void Menu::loop(const sf::Event& event){
    _game.clear();
    _game.draw();

    _playButton.update(event, _game.rw);
    _quitButton.update(event, _game.rw);

    if(_quitButton.isPressed()){
        _game.quit();
        return;
    }

    if(_playButton.isPressed()){
        _game.play();
        return;
    }

    _game.rw.draw(_playButton);
    _game.rw.draw(_quitButton);
    _game.rw.draw(_label);

    _game.rw.display();
}

void Menu::draw(){

}


