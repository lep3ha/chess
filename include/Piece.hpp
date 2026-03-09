#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "MovableSpriteComponent.hpp"
#include "Movement.hpp"
#include "BoardModel.hpp"
#include "Cell.hpp"
#include "parameters.hpp"

class Piece : public MovableSpriteComponent {
protected:
    int m_side;
    bool isSelected = false;
    Cell *m_cell;
    virtual void updateValidMoves(BoardModel boardModel) = 0;
    std::vector<Movement> m_validMoves = {};    
public:
    sf::Vector2i getCoordinates();
    bool move(Movement requestedMove, BoardModel boardModel);
    void setSide(int side);
    void select();
    void unselect();
    void setCell(Cell *cell);
    Cell *getCell();
    Piece();
    Piece(int side, Cell *standingOn);
    virtual ~Piece();
};

sf::Vector2i Piece::getCoordinates() {
    return m_cell->getCoordinates();
}

bool Piece::move(Movement requestedMove, BoardModel boardModel) {
    this->updateValidMoves(boardModel);
    if (m_validMoves.size() == 0)
        return false;

    bool isMoveCorrect = false;
    for (auto rightMove : m_validMoves) {
        if (rightMove == requestedMove) {
            isMoveCorrect = true;
            break;
        }
    }

    if (!isMoveCorrect)
        return false;


    return true;

}

void Piece::setSide(int side) {
    m_side = side;
}

void Piece::select() {
    this->isSelected = true;
}

void Piece::unselect() {
    this->isSelected = false;
}

void Piece::setCell(Cell *cell) {
    m_cell = cell;
}
Cell *Piece::getCell() {
    return m_cell;
}

Piece::Piece(int side, Cell *standingOn) {
    m_side = side;
    m_cell = standingOn;
    this->setPosition(standingOn->getPosition());
}

Piece::Piece() : MovableSpriteComponent() {}

Piece::~Piece() {}

#endif  /* PIECE_HPP */