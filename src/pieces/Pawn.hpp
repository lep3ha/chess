#ifndef PAWN_HPP
#define PAWN_HPP

#include "pieces/Piece.hpp"

class Pawn : public Piece {
  public:
    Pawn(int side, Cell *standingOn);
    void updateValidMoves(const BoardModel &boardModel) override;
};

#endif
