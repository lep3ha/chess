#include "board/BoardModel.hpp"

#include <stdexcept>

int BoardModel::isCheck() const {
    bool isWhite = false, isBlack = false;
    for (int i = 0; i < FIELD_SIDE; i++) {
        for (int j = 0; j < FIELD_SIDE; j++) {
            if (m_model[i][j].m_piece == PieceType::KING && m_model[i][j].m_side == WHITE) {
                if (m_model[i][j].attackingSide == BLACK || m_model[i][j].attackingSide == BOTH_SIDES) {
                    isWhite = true;
                }
            }
            if (m_model[i][j].m_piece == PieceType::KING && m_model[i][j].m_side == BLACK) {
                if (m_model[i][j].attackingSide == WHITE || m_model[i][j].attackingSide == BOTH_SIDES) {
                    isBlack = true;
                }
            }
        }
    }
    if (isWhite && isBlack)
        return BOTH_SIDES; // impossible board situation => invalid movement is checking;
    else if (isWhite)
        return WHITE;
    else if (isBlack)
        return BLACK;
    else
        return EMPTY;
}

CellModel &BoardModel::getCellModel(int x, int y) {
    if (x < 0 || x >= FIELD_SIDE || y < 0 || y >= FIELD_SIDE) {
        throw std::out_of_range("Board coordinates must be between 0 and 7");
    }
    return m_model[x][y];
}

CellModel &BoardModel::getCellModel(sf::Vector2i coordinates) { return getCellModel(coordinates.x, coordinates.y); }

void BoardModel::setSideByCoordinates(int x, int y, int side) { getCellModel(x, y).m_side = side; }

void BoardModel::setPieceByCoordinates(int x, int y, PieceType piece) { getCellModel(x, y).m_piece = piece; }

const CellModel &BoardModel::getCellModel(int x, int y) const {
    if (x < 0 || x >= FIELD_SIDE || y < 0 || y >= FIELD_SIDE) {
        throw std::out_of_range("Board coordinates must be between 0 and 7");
    }
    return m_model[x][y];
}

const CellModel &BoardModel::getCellModel(sf::Vector2i coordinates) const {
    return getCellModel(coordinates.x, coordinates.y);
}
