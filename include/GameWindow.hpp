#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "parameters.hpp"

class GameWindow : public sf::RenderWindow {
protected:
    virtual void onResize() override;
public:
    bool isNeededToResize = false;
    GameWindow();
    GameWindow(sf::VideoMode mode, const sf::String &title);
    ~GameWindow();
};

void GameWindow::onResize() {
    WINDOW_SIZE.x = this->getSize().x;
    WINDOW_SIZE.y = this->getSize().y;
    this->setView(sf::View(WINDOW_SIZE / (float)2, WINDOW_SIZE));    
    unsigned int formativeLength = (WINDOW_SIZE.x > WINDOW_SIZE.y) ? WINDOW_SIZE.y : WINDOW_SIZE.x;
    const int step = 15;
    for (int i = 0; i * FIELD_SIDE + i * 2.0F / 3.0F <= formativeLength; i += step) {
        CELL_SIZE = sf::Vector2f(i, i);
    }
    BORDER_THICKNESS = CELL_SIZE * 1.0F / 3.0F;
    BORDER_SIZE = CELL_SIZE * (float)FIELD_SIDE + BORDER_THICKNESS * 2.0F;    
    FIELD_START = (WINDOW_SIZE - BORDER_SIZE) / 2.0F;
    isNeededToResize = true;
}

GameWindow::GameWindow() : sf::RenderWindow() {}

GameWindow::GameWindow(sf::VideoMode mode, const sf::String &title) : sf::RenderWindow(mode, title) {
    WINDOW_SIZE.x = this->getSize().x;
    WINDOW_SIZE.y = this->getSize().y;
    this->setView(sf::View(WINDOW_SIZE / (float)2, WINDOW_SIZE));    
    unsigned int formativeLength = (WINDOW_SIZE.x > WINDOW_SIZE.y) ? WINDOW_SIZE.y : WINDOW_SIZE.x;
    const int step = 15;
    for (int i = 0; i * FIELD_SIDE + i * 1.0F / 3.0F <= formativeLength; i += step) {
        CELL_SIZE = sf::Vector2f(i, i);
    }
    BORDER_THICKNESS = CELL_SIZE * 1.0F / 3.0F;
    BORDER_SIZE = CELL_SIZE * (float)FIELD_SIDE + BORDER_THICKNESS * 2.0F;    
    FIELD_START = (WINDOW_SIZE - BORDER_SIZE) / 2.0F;
    // std::cout << "WINDOW_SIZE: " << WINDOW_SIZE.x << " " << WINDOW_SIZE.y << "\n";
    // std::cout << "CELL_SIZE: " << CELL_SIZE.x << "\n";
    // std::cout << "FIELD_START: " << FIELD_START.x << " " << FIELD_START.y << "\n";
    // std::cout << "BORDER_THICKNESS: " << BORDER_THICKNESS.x << "\n";
    // std::cout << "BORDER_SIZE: " << BORDER_SIZE.x << " " << BORDER_SIZE.y << "\n";
}

GameWindow::~GameWindow() {}

#endif /* GAME_WINDOW_HPP */