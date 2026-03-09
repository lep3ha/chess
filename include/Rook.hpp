#ifndef ROOK_HPP
#define ROOK_HPP

#include <SFML/Graphics.hpp>

#include "Piece.hpp"

class Rook : public Piece {
private:
    bool wasFirstMove = false;
public:
    virtual void updateValidMoves(BoardModel boardModel) override;
    
    Rook(int side, Cell *standingOn);
    ~Rook();
};

void Rook::updateValidMoves(BoardModel boardModel) {
    m_validMoves.clear();
    Movement potentialMove;
    potentialMove.fromCellCoordinates = this->getCoordinates();
    sf::Vector2i difference[4] = {
        sf::Vector2i(0, 1),     
        sf::Vector2i(0, -1),    
        sf::Vector2i(1, 0),    
        sf::Vector2i(-1, 0) 
    };
    for (sf::Vector2i shift : difference) {
        for (sf::Vector2i newCoordinates = this->getCoordinates(); 
        (newCoordinates.x < FIELD_SIDE && newCoordinates.x >= 0) && (newCoordinates.y < FIELD_SIDE && newCoordinates.y >= 0); 
        newCoordinates += shift) {
            if (boardModel.getCellModel(newCoordinates).m_side == m_side) 
                break;
            else if (boardModel.getCellModel(newCoordinates).m_side == -m_side) {
                potentialMove.type = MovementType::CAPTURE;
                potentialMove.toCellCoordinates = newCoordinates;
                m_validMoves.push_back(potentialMove);
                break;
            }
            else {
                potentialMove.type = MovementType::DEFAULT;
                potentialMove.toCellCoordinates = newCoordinates;
                m_validMoves.push_back(potentialMove);                
            }
        }
    }
}

Rook::Rook(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == -1)
        this->initWithPath(BLACK_ROOK_PATH);
    else    
        this->initWithPath(WHITE_ROOK_PATH);
    this->setSize(CELL_SIZE);
}

Rook::~Rook() {}

#endif  /* ROOK_HPP */