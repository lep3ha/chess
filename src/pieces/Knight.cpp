#include "pieces/Knight.hpp"

void Knight::updateValidMoves(const BoardModel &boardModel) {
    m_validMoves.clear();
    Movement potentialMove{};
    potentialMove.fromCellCoordinates = this->getCoordinates();
    sf::Vector2i difference[8] = {sf::Vector2i(2, 1),   sf::Vector2i(2, -1), sf::Vector2i(1, -2), sf::Vector2i(-1, -2),
                                  sf::Vector2i(-2, -1), sf::Vector2i(-2, 1), sf::Vector2i(-1, 2), sf::Vector2i(1, 2)};
    for (sf::Vector2i shift : difference) {
        sf::Vector2i newCoordinates = this->getCoordinates() + shift;
        if ((newCoordinates.x < FIELD_SIDE && newCoordinates.x >= 0) &&
            (newCoordinates.y < FIELD_SIDE && newCoordinates.y >= 0)) {
            if (boardModel.getCellModel(newCoordinates).m_side == m_side)
                continue;
            else if (boardModel.getCellModel(newCoordinates).m_side == -m_side) {
                potentialMove.type = MovementType::CAPTURE;
                potentialMove.toCellCoordinates = newCoordinates;
                m_validMoves.push_back(potentialMove);
            } else {
                potentialMove.type = MovementType::DEFAULT;
                potentialMove.toCellCoordinates = newCoordinates;
                m_validMoves.push_back(potentialMove);
            }
        }
    }
}

Knight::Knight(int side, Cell *standingOn) : Piece(side, standingOn) {
    if (side == BLACK)
        this->initWithPath("images/themes/wooden/blackKnight.png");
    else
        this->initWithPath("images/themes/wooden/whiteKnight.png");
}
