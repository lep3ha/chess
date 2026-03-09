#ifndef KING_HPP
#define KING_HPP

#include <SFML/Graphics.hpp>

#include "Piece.hpp"

class King : public Piece {
private:
    bool wasFirstMove = false;
public:
    virtual void updateValidMoves(BoardModel boardModel) override;
    
    King(int side, Cell *standingOn);
    ~King();   

};

void King::updateValidMoves(BoardModel boardModel) {

}

King::King(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == -1)
        this->initWithPath(BLACK_KING_PATH);
    else    
        this->initWithPath(WHITE_KING_PATH);
    this->setSize(CELL_SIZE);
}

King::~King() {}

#endif  /* KING_HPP */