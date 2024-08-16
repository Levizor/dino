#include "Menu.h"
#include "Button.h"

#include "Game.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "fmt/core.h"


void Menu::init(){
    _playButton = Button(" Play");
    _quitButton = Button(" Quit");
    _repeatButton = Button("Repeat" );
    _MenuButton = Button(" Menu");


    _menuButtons.push_back(&_playButton);
    _menuButtons.push_back(&_quitButton);

    _gameOverButtons.push_back(&_repeatButton);
    _gameOverButtons.push_back(&_MenuButton);
    


    int gap = 120;
    sf::Vector2u ws = _game.rw.getSize();
    sf::Vector2f lastPos = sf::Vector2f(ws.x-250, ws.y/2.);

    
    for(Button* button: _menuButtons){
        button->setPosition(lastPos.x, lastPos.y);
        button->setFont(*_game.om.getFont());
        button->setSize(200, 100);
        lastPos.y = lastPos.y + gap;
    }

    lastPos=sf::Vector2f(ws.x/2.-100, ws.y/2.-50);

    for(Button* button: _gameOverButtons){
        button->setPosition(ws.x/2.-100, lastPos.y);
        button->setSize(200, 100);
        button->setFont(*_game.om.getFont());
        lastPos.y = lastPos.y + gap;
    }


    _label.setFont(*_game.om.getFont());
    _label.setFillColor(sf::Color(0x12664fff));
    _label.setCharacterSize(200);
    _label.setString("Dino");
    _label.setPosition(ws.x-560, ws.y/2.-300);

    
    _bsLabel.setFont(*_game.om.getFont());
    _bsLabel.setFillColor(sf::Color(0xf7b801ff));
    _bsLabel.setCharacterSize(50);
    updateScore();
    _bsLabel.setOrigin(0, _bsLabel.getGlobalBounds().height);
    _bsLabel.setPosition(10, ws.y-70);
}

void Menu::loop(const sf::Event& event){

    _playButton.update(event, _game.rw);
    _quitButton.update(event, _game.rw);

    _game.clear();
    _game.draw();
    _game.rw.draw(_playButton);
    _game.rw.draw(_quitButton);
    _game.rw.draw(_label);
    _game.rw.draw(_bsLabel);
    _game.display();


    if(_quitButton.isPressed() or sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        _game.setState(Exiting);
        return;
    }

    if(_playButton.isPressed() or sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        _game.setState(Playing);
        return;
    }

}

void Menu::draw(){

}


void Menu::gameOverLoop(const sf::Event& event){
    _repeatButton.update(event, _game.rw);
    _MenuButton.update(event, _game.rw);

    _game.clear();
    _game.draw();
    _game.rw.draw(_repeatButton);
    _game.rw.draw(_MenuButton);
    _game._run.drawScores();
    _game.display();

    if(_repeatButton.isPressed() or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        _game.setState(Playing);
        return;
    } 

    if(_MenuButton.isPressed() or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
        _game.setState(InMenu);
        return;
    }



}

void Menu::updateScore(){
    _bsLabel.setString(fmt::format("HI: {:08}", _game.getBestScore()));
}

