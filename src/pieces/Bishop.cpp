#include "pieces/Bishop.hpp"

void Bishop::updateValidMoves(const BoardModel &boardModel) {
    m_validMoves.clear();
    Movement potentialMove{};
    potentialMove.fromCellCoordinates = this->getCoordinates();
    sf::Vector2i difference[4] = {sf::Vector2i(1, 1), sf::Vector2i(-1, 1), sf::Vector2i(1, -1), sf::Vector2i(-1, -1)};
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

Bishop::Bishop(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == BLACK)
        this->initWithPath("images/themes/wooden/blackBishop.png");
    else
        this->initWithPath("images/themes/wooden/whiteBishop.png");
}
