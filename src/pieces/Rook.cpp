#include "pieces/Rook.hpp"

void Rook::updateValidMoves(const BoardModel &boardModel) {
    m_validMoves.clear();
    Movement potentialMove{};
    potentialMove.fromCellCoordinates = this->getCoordinates();
    sf::Vector2i difference[4] = {sf::Vector2i(0, 1), sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(-1, 0)};
    for (sf::Vector2i shift : difference) {
        for (sf::Vector2i newCoordinates = this->getCoordinates() + shift;
             (newCoordinates.x < FIELD_SIDE && newCoordinates.x >= 0) &&
             (newCoordinates.y < FIELD_SIDE && newCoordinates.y >= 0);
             newCoordinates += shift) {
            if (boardModel.getCellModel(newCoordinates).m_side == m_side)
                break;
            else if (boardModel.getCellModel(newCoordinates).m_side == -m_side) {
                potentialMove.type = MovementType::CAPTURE;
                potentialMove.toCellCoordinates = newCoordinates;
                m_validMoves.push_back(potentialMove);
                break;
            } else {
                potentialMove.type = MovementType::DEFAULT;
                potentialMove.toCellCoordinates = newCoordinates;
                m_validMoves.push_back(potentialMove);
            }
        }
    }
}

Rook::Rook(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == BLACK)
        this->initWithPath("images/themes/wooden/blackRook.png");
    else
        this->initWithPath("images/themes/wooden/whiteRook.png");
}
