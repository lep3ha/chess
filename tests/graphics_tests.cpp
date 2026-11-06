#include <array>
#include <exception>
#include <iostream>
#include <type_traits>

#include "app/GameWindow.hpp"
#include "board/Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "support/TestSupport.hpp"

namespace {
void testBoard() {
    const auto layout = BoardLayout::fromWindowSize({800, 600});
    Board board(layout);
    constexpr std::array<PieceType, FIELD_SIDE> backRank = {PieceType::ROOK,   PieceType::KNIGHT, PieceType::BISHOP,
                                                            PieceType::QUEEN,  PieceType::KING,   PieceType::BISHOP,
                                                            PieceType::KNIGHT, PieceType::ROOK};
    int pieceCount = 0;
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            Cell *cell = board.getCell(x, y);
            require(cell->getCoordinates() == sf::Vector2i(x, y), "Cell coordinates must match model indices");
            const auto center = cell->getPosition() + layout.cellSize / 2.0F;
            require(cell->isContains(sf::Vector2i(center)), "Cell must contain its visual center");
            Piece *piece = board.getPieceByCoordinates(x, y);
            const auto &model = board.getCellModel(x, y);
            if (y >= 2 && y <= 5) {
                require(piece == nullptr && model.m_piece == PieceType::NONE && model.m_side == EMPTY,
                        "Middle ranks must be empty");
                continue;
            }
            ++pieceCount;
            require(piece != nullptr && piece->getCell() == cell, "Piece and model must use the same square");
            require(piece->getPosition() == cell->getPosition(), "Piece must be rendered on its own square");
            require(model.m_side == (y < 2 ? WHITE : BLACK), "Initial side must match rank");
            require(model.m_piece == ((y == 1 || y == 6) ? PieceType::PAWN : backRank[x]),
                    "Initial piece must match rank and file");
        }
    }
    require(pieceCount == 32 && board.isCheck() == EMPTY, "Initial position has 32 pieces and no check");
    require(board.getCell(0, 0)->getPosition().y > board.getCell(0, 7)->getPosition().y,
            "White ranks must be at the bottom");
    requireThrows<std::out_of_range>([&] { board.getCell(8, 0); }, "Board view must check bounds");
    const auto resized = BoardLayout::fromWindowSize({120, 90});
    board.resize(resized);
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            const auto center = board.getCell(x, y)->getPosition() + resized.cellSize / 2.0F;
            require(board.getCell(x, y)->isContains(sf::Vector2i(center)), "Resized cells must remain clickable");
            if (const auto *piece = board.getPieceByCoordinates(x, y)) {
                require(piece->getPosition() == board.getCell(x, y)->getPosition(), "Resize must also move pieces");
            }
        }
    }
}

void testExistingMoveGenerators() {
    Cell origin;
    origin.setCoordinates({3, 3});
    BoardModel model;
    model.getCellModel(3, 3) = {PieceType::ROOK, WHITE, EMPTY};
    Rook rook(WHITE, &origin);
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            const bool expected = (x == 3 || y == 3) && !(x == 3 && y == 3);
            require(rook.move({DEFAULT, {x, y}, {3, 3}}, model) == expected, "Rook must scan all four rays");
        }
    }
    model.getCellModel(3, 5) = {PieceType::PAWN, WHITE, EMPTY};
    model.getCellModel(1, 3) = {PieceType::PAWN, BLACK, EMPTY};
    require(!rook.move({DEFAULT, {3, 5}, {3, 3}}, model), "Rook cannot enter a friendly square");
    require(!rook.move({DEFAULT, {3, 6}, {3, 3}}, model), "Rook cannot pass through a friendly piece");
    require(rook.move({CAPTURE, {1, 3}, {3, 3}}, model), "Rook can capture the first enemy on a ray");
    require(!rook.move({DEFAULT, {0, 3}, {3, 3}}, model), "Rook must stop after capture");
    require(!rook.move({DEFAULT, {1, 3}, {3, 3}}, model), "Capture must use the capture movement type");

    model = BoardModel{};
    model.getCellModel(3, 3) = {PieceType::BISHOP, WHITE, EMPTY};
    Bishop bishop(WHITE, &origin);
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            const bool expected = std::abs(x - 3) == std::abs(y - 3) && x != 3;
            require(bishop.move({DEFAULT, {x, y}, {3, 3}}, model) == expected, "Bishop must scan all diagonals");
        }
    }
    model.getCellModel(5, 5) = {PieceType::PAWN, WHITE, EMPTY};
    model.getCellModel(1, 1) = {PieceType::PAWN, BLACK, EMPTY};
    require(!bishop.move({DEFAULT, {6, 6}, {3, 3}}, model), "Bishop cannot pass through a friendly piece");
    require(bishop.move({CAPTURE, {1, 1}, {3, 3}}, model), "Bishop can capture an enemy");
    require(!bishop.move({DEFAULT, {0, 0}, {3, 3}}, model), "Bishop must stop after capture");

    model = BoardModel{};
    model.getCellModel(3, 3) = {PieceType::KNIGHT, WHITE, EMPTY};
    Knight knight(WHITE, &origin);
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            const int dx = std::abs(x - 3), dy = std::abs(y - 3);
            const bool expected = (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
            require(knight.move({DEFAULT, {x, y}, {3, 3}}, model) == expected, "Knight must consider all eight jumps");
        }
    }
    model.getCellModel(5, 4) = {PieceType::PAWN, WHITE, EMPTY};
    model.getCellModel(5, 2) = {PieceType::PAWN, BLACK, EMPTY};
    require(!knight.move({DEFAULT, {5, 4}, {3, 3}}, model), "Knight cannot enter a friendly square");
    require(knight.move({CAPTURE, {5, 2}, {3, 3}}, model), "Knight must consider capture after a blocked candidate");
    require(knight.move({DEFAULT, {4, 1}, {3, 3}}, model), "Knight must continue after a capture candidate");
    origin.setCoordinates({0, 0});
    require(knight.move({DEFAULT, {1, 2}, {0, 0}}, model), "Knight must handle board corners");
    require(!knight.move({DEFAULT, {-1, 2}, {0, 0}}, model), "Knight must reject off-board destinations");
    require(!rook.move({DEFAULT, {0, 1}, {3, 3}}, model), "Move origin must match the piece coordinates");
}

void testResourceErrors() {
    SpriteComponent sprite;
    requireThrows<std::logic_error>([&] { sprite.setSize({10, 10}); }, "Unloaded textures cannot be scaled");
    requireThrows<std::invalid_argument>([&] { sprite.initWithPath(""); }, "Empty texture paths must be rejected");
    requireThrows<std::runtime_error>([&] { sprite.initWithPath("missing-texture.png"); },
                                      "Missing textures must report a load error");
    requireThrows<std::invalid_argument>([] { Rook invalid(WHITE, nullptr); }, "Null cells must be rejected");
}

void testWindowResize() {
    GameWindow window(sf::VideoMode(800, 600), "Chess test");
    window.setVisible(false);
    require(window.getLayout().windowSize == sf::Vector2f(800, 600), "Initial layout must match window size");
    window.setSize({100, 80});
    require(window.getLayout().windowSize == sf::Vector2f(100, 80), "Resize must refresh window layout");
    require(window.getLayout().borderSize.x <= 100 && window.getLayout().borderSize.y <= 80,
            "Small windows must contain the full board");
    window.close();
}
} // namespace

int main() {
    static_assert(!std::is_copy_constructible_v<Board> && !std::is_move_constructible_v<Board>);
    static_assert(!std::is_copy_constructible_v<SpriteComponent>);
    try {
        testBoard();
        testExistingMoveGenerators();
        testResourceErrors();
        testWindowResize();
        std::cout << "Graphics tests passed\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
