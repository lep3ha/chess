#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "pieces/Piece.hpp"

class Queen : public Piece {
  public:
    Queen(int side, Cell *standingOn);
    void updateValidMoves(const BoardModel &boardModel) override;
};

#endif
