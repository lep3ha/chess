#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "pieces/Piece.hpp"

class Bishop : public Piece {
  public:
    Bishop(int side, Cell *standingOn);
    void updateValidMoves(const BoardModel &boardModel) override;
};

#endif
