#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "pieces/Piece.hpp"

class Knight : public Piece {
  public:
    Knight(int side, Cell *standingOn);
    void updateValidMoves(const BoardModel &boardModel) override;
};

#endif
