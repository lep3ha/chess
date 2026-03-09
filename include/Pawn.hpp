#ifndef PAWN_HPP
#define PAWN_HPP

#include <SFML/Graphics.hpp>

#include "Piece.hpp"
#include "Cell.hpp"

class Pawn : public Piece {
private:
    bool wasFirstMove = false;
public:
    virtual void updateValidMoves(BoardModel boardModel) override;
    
    Pawn(int side, Cell *standingOn);
    ~Pawn();   

};

void Pawn::updateValidMoves(BoardModel boardModel) {

}

Pawn::Pawn(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == -1)
        this->initWithPath(BLACK_PAWN_PATH);
    else    
        this->initWithPath(WHITE_PAWN_PATH);
    this->setSize(CELL_SIZE);
}

Pawn::~Pawn() {}

#endif  /* PAWN_HPP */