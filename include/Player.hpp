#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include "Piece.hpp"
#include "Cell.hpp"
#include "parameters.hpp"

class Player {
private:
    bool isWinner = false;
    std::vector<Piece> allFigures;

public:
    void renderFigures(sf::RenderWindow &renderWindow);
    Player(int side);
    Player();
    ~Player();
};

void Player::renderFigures(sf::RenderWindow &renderWindow) {
    for (int i = 0; i < allFigures.size(); i++) {
        allFigures[i].render(renderWindow);
    }
}

Player::Player(int side) {
    
}

Player::Player() {

}

Player::~Player() {

}

#endif  /* PLAYER_HPP */