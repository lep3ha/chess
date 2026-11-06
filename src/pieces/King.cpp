#include "pieces/King.hpp"

King::King(int side, Cell *standingOn) : Piece(side, standingOn) {
    initWithPath(side == BLACK ? "images/themes/wooden/blackKing.png" : "images/themes/wooden/whiteKing.png");
}

void King::updateValidMoves(const BoardModel &) {
    // Move generation was unfinished in the original project.
    m_validMoves.clear();
}
