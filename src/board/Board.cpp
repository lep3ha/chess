#include "board/Board.hpp"

#include <array>
#include <stdexcept>

#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"

namespace {
std::unique_ptr<Piece> makePiece(PieceType type, int side, Cell *cell) {
    switch (type) {
    case PieceType::ROOK:
        return std::make_unique<Rook>(side, cell);
    case PieceType::KNIGHT:
        return std::make_unique<Knight>(side, cell);
    case PieceType::BISHOP:
        return std::make_unique<Bishop>(side, cell);
    case PieceType::QUEEN:
        return std::make_unique<Queen>(side, cell);
    case PieceType::KING:
        return std::make_unique<King>(side, cell);
    case PieceType::PAWN:
        return std::make_unique<Pawn>(side, cell);
    case PieceType::NONE:
        break;
    }
    throw std::invalid_argument("Cannot create an empty piece");
}
} // namespace

Board::Board(const BoardLayout &layout) {
    constexpr std::array<PieceType, FIELD_SIDE> backRank = {PieceType::ROOK,   PieceType::KNIGHT, PieceType::BISHOP,
                                                            PieceType::QUEEN,  PieceType::KING,   PieceType::BISHOP,
                                                            PieceType::KNIGHT, PieceType::ROOK};
    m_border.initWithPath(BORDER_PATH);
    m_allFigures.reserve(32);
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            Cell &cell = m_field[x][y];
            cell.initWithPath((x + y) % 2 == 0 ? BLACK_CELL_PATH : WHITE_CELL_PATH);
            cell.setCoordinates({x, y});
            if (y > 1 && y < FIELD_SIDE - 2) {
                continue;
            }
            const int side = y < 2 ? WHITE : BLACK;
            const PieceType type = (y == 1 || y == FIELD_SIDE - 2) ? PieceType::PAWN : backRank[x];
            m_model[x][y] = {type, side, EMPTY};
            m_allFigures.push_back(makePiece(type, side, &cell));
        }
    }
    resize(layout);
}

Cell *Board::getCell(int x, int y) {
    // Reuse the model's bounds check before indexing the corresponding view.
    getCellModel(x, y);
    return &m_field[x][y];
}

Piece *Board::getPieceByCoordinates(int x, int y) const {
    for (const auto &piece : m_allFigures) {
        if (piece->getCoordinates() == sf::Vector2i(x, y)) {
            return piece.get();
        }
    }
    return nullptr;
}

void Board::render(sf::RenderWindow &renderWindow) const {
    m_border.render(renderWindow);
    for (const auto &column : m_field) {
        for (const auto &cell : column) {
            cell.render(renderWindow);
        }
    }
    for (const auto &piece : m_allFigures) {
        piece->render(renderWindow);
    }
}

void Board::resize(const BoardLayout &layout) {
    m_border.setSize(layout.borderSize);
    m_border.setPosition(layout.fieldStart);
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            Cell &cell = m_field[x][y];
            cell.setSize(layout.cellSize);
            cell.setPosition(layout.fieldStart + layout.borderThickness +
                             sf::Vector2f(static_cast<float>(x), static_cast<float>(FIELD_SIDE - y - 1)) *
                                 layout.cellSize.x);
        }
    }
    for (const auto &piece : m_allFigures) {
        piece->setSize(layout.cellSize);
        piece->setPosition(piece->getCell()->getPosition());
    }
}
