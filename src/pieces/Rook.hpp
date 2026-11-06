#ifndef ROOK_HPP
#define ROOK_HPP

#include "pieces/Piece.hpp"

class Rook : public Piece {
  public:
    Rook(int side, Cell *standingOn);
    void updateValidMoves(const BoardModel &boardModel) override;
};

#endif
