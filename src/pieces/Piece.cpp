#include "pieces/Piece.hpp"

#include <algorithm>
#include <stdexcept>

sf::Vector2i Piece::getCoordinates() const { return m_cell->getCoordinates(); }

bool Piece::move(const Movement &requestedMove, const BoardModel &boardModel) {
    updateValidMoves(boardModel);
    return std::find(m_validMoves.begin(), m_validMoves.end(), requestedMove) != m_validMoves.end();
}

void Piece::setSide(int side) { m_side = side; }

void Piece::select() { this->isSelected = true; }

void Piece::unselect() { this->isSelected = false; }

void Piece::setCell(Cell *cell) {
    if (cell == nullptr) {
        throw std::invalid_argument("A piece must belong to a cell");
    }
    m_cell = cell;
}
Cell *Piece::getCell() const { return m_cell; }

Piece::Piece(int side, Cell *standingOn) : m_side(side), m_cell(standingOn) {
    setCell(standingOn);
    setPosition(standingOn->getPosition());
}
