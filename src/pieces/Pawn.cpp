#include "pieces/Pawn.hpp"

Pawn::Pawn(int side, Cell *standingOn) : Piece(side, standingOn) {
    initWithPath(side == BLACK ? "images/themes/wooden/blackPawn.png" : "images/themes/wooden/whitePawn.png");
}

void Pawn::updateValidMoves(const BoardModel &) {
    // Move generation was unfinished in the original project.
    m_validMoves.clear();
}
