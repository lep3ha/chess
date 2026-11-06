#ifndef KING_HPP
#define KING_HPP

#include "pieces/Piece.hpp"

class King : public Piece {
  public:
    King(int side, Cell *standingOn);
    void updateValidMoves(const BoardModel &boardModel) override;
};

#endif
