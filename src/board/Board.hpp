#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory>
#include <vector>

#include "board/BoardLayout.hpp"
#include "board/BoardModel.hpp"
#include "board/Cell.hpp"
#include "pieces/Piece.hpp"

class Board : public BoardModel {
  private:
    Cell m_field[FIELD_SIDE][FIELD_SIDE];
    std::vector<std::unique_ptr<Piece>> m_allFigures;
    SpriteComponent m_border;

  public:
    explicit Board(const BoardLayout &layout);
    Cell *getCell(int x, int y);
    Piece *getPieceByCoordinates(int x, int y) const;
    void render(sf::RenderWindow &renderWindow) const;
    void resize(const BoardLayout &layout);
};

#endif
