#include <array>
#include <cmath>
#include <exception>
#include <iostream>

#include "board/BoardLayout.hpp"
#include "board/BoardModel.hpp"
#include "pieces/Movement.hpp"
#include "support/TestSupport.hpp"

namespace {
void testModel() {
    BoardModel model;
    for (int x = 0; x < FIELD_SIDE; ++x) {
        for (int y = 0; y < FIELD_SIDE; ++y) {
            const auto &cell = model.getCellModel(x, y);
            require(cell.m_piece == PieceType::NONE && cell.m_side == EMPTY && cell.attackingSide == EMPTY,
                    "Default cells must be empty and unattacked");
        }
    }
    require(model.isCheck() == EMPTY, "An empty board has no king in check");
    model.getCellModel(4, 0) = {PieceType::KING, WHITE, BLACK};
    model.getCellModel(4, 7) = {PieceType::KING, BLACK, EMPTY};
    require(model.isCheck() == WHITE, "White king in check");
    model.getCellModel(4, 7).attackingSide = BOTH_SIDES;
    require(model.isCheck() == BOTH_SIDES, "Both kings in check");
    model.getCellModel(4, 0).attackingSide = EMPTY;
    require(model.isCheck() == BLACK, "Black king in check");

    const BoardModel copy(model);
    BoardModel assigned;
    assigned = model;
    model.getCellModel(4, 7) = {};
    for (const BoardModel *snapshot : std::array<const BoardModel *, 2>{&copy, &assigned}) {
        require(snapshot->isCheck() == BLACK, "Copy must preserve an independent board state");
        require(snapshot->getCellModel({4, 7}).attackingSide == BOTH_SIDES, "Copy must preserve attack metadata");
    }
    requireThrows<std::out_of_range>([&] { model.getCellModel(-1, 0); }, "Negative coordinates must be rejected");
    requireThrows<std::out_of_range>([&] { copy.getCellModel(0, FIELD_SIDE); }, "Const access must check bounds");
    requireThrows<std::out_of_range>([&] { model.setSideByCoordinates(8, 0, WHITE); }, "Side setter must check bounds");
    requireThrows<std::out_of_range>([&] { model.setPieceByCoordinates(0, -1, PieceType::PAWN); },
                                     "Piece setter must check bounds");
}

void testLayout() {
    for (const sf::Vector2u size : {sf::Vector2u(1920, 1080), sf::Vector2u(800, 600), sf::Vector2u(600, 800),
                                    sf::Vector2u(100, 80), sf::Vector2u(1, 1), sf::Vector2u(0, 0)}) {
        const auto layout = BoardLayout::fromWindowSize(size);
        require(std::isfinite(layout.cellSize.x) && layout.cellSize.x >= 0, "Cell size must be finite and nonnegative");
        require(layout.cellSize.x == layout.cellSize.y, "Cells must remain square");
        require(layout.fieldStart.x >= -0.001F && layout.fieldStart.y >= -0.001F, "Border must fit inside window");
        require(layout.borderSize.x <= static_cast<float>(size.x) + 0.001F &&
                    layout.borderSize.y <= static_cast<float>(size.y) + 0.001F,
                "Board and both borders must fit inside window");
        require(std::abs(layout.fieldStart.x * 2 + layout.borderSize.x - static_cast<float>(size.x)) < 0.001F,
                "Board must remain centered horizontally");
        require(std::abs(layout.fieldStart.y * 2 + layout.borderSize.y - static_cast<float>(size.y)) < 0.001F,
                "Board must remain centered vertically");
    }
}

void testMovementEquality() {
    const Movement move{CAPTURE, {2, 3}, {0, 1}};
    require(move == Movement{CAPTURE, {2, 3}, {0, 1}}, "Equal moves must compare equal");
    require(!(move == Movement{DEFAULT, {2, 3}, {0, 1}}), "Movement type participates in equality");
    require(!(move == Movement{CAPTURE, {3, 2}, {0, 1}}), "Destination participates in equality");
    require(!(move == Movement{CAPTURE, {2, 3}, {1, 0}}), "Origin participates in equality");
}
} // namespace

int main() {
    try {
        testModel();
        testLayout();
        testMovementEquality();
        std::cout << "Model tests passed\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
