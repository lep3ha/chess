#include "pieces/Queen.hpp"

Queen::Queen(int side, Cell *standingOn) : Piece(side, standingOn) {
    initWithPath(side == BLACK ? "images/themes/wooden/blackQueen.png" : "images/themes/wooden/whiteQueen.png");
}

void Queen::updateValidMoves(const BoardModel &) {
    // Move generation was unfinished in the original project.
    m_validMoves.clear();
}
