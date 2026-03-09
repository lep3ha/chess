#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <SFML/Graphics.hpp>

#include "Piece.hpp"

class Queen : public Piece {
public:
    virtual void updateValidMoves(BoardModel boardModel) override;
    
    Queen(int side, Cell *standingOn);
    ~Queen();   

};

void Queen::updateValidMoves(BoardModel boardModel) {
    m_validMoves.clear();
    Movement potentialMove;
    potentialMove.fromCellCoordinates = this->getCoordinates();
    sf::Vector2i difference[8] = {
        sf::Vector2i(1, 1),     
        sf::Vector2i(-1, 1),    
        sf::Vector2i(1, -1),    
        sf::Vector2i(-1, -1),
        sf::Vector2i(0, -1), 
        sf::Vector2i(0, 1), 
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
                BoardModel potentialBoardSituation(boardModel);
            }
        }
    }
}

Queen::Queen(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == -1)
        this->initWithPath(BLACK_QUEEN_PATH);
    else    
        this->initWithPath(WHITE_QUEEN_PATH);
    this->setSize(CELL_SIZE);
}

Queen::~Queen() {}

#endif  /* QUEEN_HPP */