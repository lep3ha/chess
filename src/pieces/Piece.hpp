#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

#include "board/BoardModel.hpp"
#include "board/Cell.hpp"
#include "graphics/MovableSpriteComponent.hpp"
#include "pieces/Movement.hpp"

class Piece : public MovableSpriteComponent {
  protected:
    int m_side;
    bool isSelected = false;
    Cell *m_cell; // Non-owning; the board owns all cells and outlives its pieces.
    std::vector<Movement> m_validMoves;
    virtual void updateValidMoves(const BoardModel &boardModel) = 0;

  public:
    Piece(int side, Cell *standingOn);
    ~Piece() override = default;

    sf::Vector2i getCoordinates() const;
    // Validates a candidate only. Applying a move is not implemented in this prototype.
    bool move(const Movement &requestedMove, const BoardModel &boardModel);
    void setSide(int side);
    void select();
    void unselect();
    void setCell(Cell *cell);
    Cell *getCell() const;
};

#endif
