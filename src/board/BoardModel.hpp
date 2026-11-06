#ifndef BOARD_MODEL_HPP
#define BOARD_MODEL_HPP

#include <SFML/System/Vector2.hpp>

#include "board/CellModel.hpp"

class BoardModel {
  protected:
    CellModel m_model[FIELD_SIDE][FIELD_SIDE]{};

  public:
    int isCheck() const;
    CellModel &getCellModel(int x, int y);
    const CellModel &getCellModel(int x, int y) const;
    CellModel &getCellModel(sf::Vector2i coordinates);
    const CellModel &getCellModel(sf::Vector2i coordinates) const;
    void setSideByCoordinates(int x, int y, int side);
    void setPieceByCoordinates(int x, int y, PieceType piece);
};

#endif
