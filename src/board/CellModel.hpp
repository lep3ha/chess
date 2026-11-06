#ifndef CELL_MODEL_HPP
#define CELL_MODEL_HPP

#include "Config.hpp"

struct CellModel {
    PieceType m_piece = PieceType::NONE;
    int m_side = EMPTY;
    int attackingSide = EMPTY;
};

#endif
