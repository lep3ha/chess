#ifndef BOARD_MODEL_HPP
#define BOARD_MODEL_HPP

#include "CellModel.hpp"

class BoardModel {
protected:    
    CellModel m_model[FIELD_SIDE][FIELD_SIDE];
public:
    int isCheck();
    CellModel &getCellModel(int x, int y);
    CellModel &getCellModel(sf::Vector2i coordinates);
    void setSideByCoordinates(int x, int y, int side);
    void setPieceByCoordinates(int x, int y, PieceType piece);
    BoardModel();
    BoardModel(const BoardModel &sample);
    ~BoardModel();
};

int BoardModel::isCheck() {
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
    return m_model[x][y];
}

CellModel &BoardModel::getCellModel(sf::Vector2i coordinates) {
    return m_model[coordinates.x][coordinates.y];
}

void BoardModel::setSideByCoordinates(int x, int y, int side) {
    m_model[x][y].m_side = side;
}

void BoardModel::setPieceByCoordinates(int x, int y, PieceType piece) {
    m_model[x][y].m_piece = piece;
}

BoardModel::BoardModel() {}

BoardModel::BoardModel(const BoardModel &sample) {
    BoardModel copy;
    for (int i = 0; i < FIELD_SIDE; i++) {
        for (int j = 0; j < FIELD_SIDE; j++) {
            copy.m_model[i][j] = sample.m_model[i][j];
        }
    }
}

BoardModel::~BoardModel() {}

#endif /* BOARD_MODEL_HPP */