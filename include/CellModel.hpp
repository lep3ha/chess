#ifndef CELL_MODEL_HPP
#define CELL_MODEL_HPP

#include "parameters.hpp"

struct CellModel {
    PieceType m_piece;
    int m_side;
    int attackingSide;
};


#endif /* CELL_MODEL_HPP */