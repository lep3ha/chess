#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameWindow.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include "parameters.hpp"

class Game {
private:
    Player m_whitePlayer;
    Player m_blackPlayer;
    bool isEnded = false;
    Board m_board;
    SpriteComponent backgroundImage;
public:
    void play(GameWindow &renderWindow);
    void end(sf::RenderWindow &renderWindow);
    void start(sf::RenderWindow &renderWindow);
    Game();
    ~Game();
};

void Game::play(GameWindow &renderWindow) {
    bool wasMouseButtonReleased = false;
    sf::Vector2i mousePosition;
    while (renderWindow.isOpen()) {
        mousePosition = sf::Mouse::getPosition(renderWindow);
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                renderWindow.close();
            if (event.type == sf::Event::MouseButtonReleased)
                wasMouseButtonReleased = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && wasMouseButtonReleased) {
            for (int i = 0; i < FIELD_SIDE; i++) {
                for (int j = 0; j < FIELD_SIDE; j++) {
                    if (m_board.getCell(i, j)->isContains(mousePosition)) {
                        std::cout << (char)('a' + i) << " " << j + 1 << "\n";
                        //std::cout << i << " " << j << "\n";
                    }
                }
            }

            wasMouseButtonReleased = false;
        }

        renderWindow.clear();
        if (renderWindow.isNeededToResize) {
            m_board.resize();
            renderWindow.isNeededToResize = false;
        }
        backgroundImage.render(renderWindow);
        m_board.render(renderWindow);
        
        renderWindow.display();
    }
}

Game::Game() {
    backgroundImage.initWithPath(BACKGROUND_IMAGE_PATH);
}

Game::~Game() {}

#endif /* GAME_HPP */