#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <SFML/Graphics.hpp>

#include "Piece.hpp"

class Knight : public Piece {
public:
    virtual void updateValidMoves(BoardModel boardModel) override;
    
    Knight(int side, Cell *standingOn);
    ~Knight();   

};

void Knight::updateValidMoves(BoardModel boardModel) {
    m_validMoves.clear();
    Movement potentialMove;
    potentialMove.fromCellCoordinates = this->getCoordinates();
    sf::Vector2i difference[8] = {
        sf::Vector2i(2, 1),     
        sf::Vector2i(2, -1),    
        sf::Vector2i(1, -2),    
        sf::Vector2i(-1, -2),
        sf::Vector2i(-2, -1), 
        sf::Vector2i(-2, 1), 
        sf::Vector2i(-1, 2), 
        sf::Vector2i(1, 2)
    };
    for (sf::Vector2i shift : difference) {
        sf::Vector2i newCoordinates = this->getCoordinates() + shift;
        if ((newCoordinates.x <= 7 && newCoordinates.x >= 0) && (newCoordinates.y <= 7 && newCoordinates.y >= 0)) {
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
                break;    
            }
        }
    }
}

Knight::Knight(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == -1)
        this->initWithPath(BLACK_KNIGHT_PATH);
    else    
        this->initWithPath(WHITE_KNIGHT_PATH);
    this->setSize(CELL_SIZE);
}

Knight::~Knight() {}

#endif  /* KNIGHT_HPP */