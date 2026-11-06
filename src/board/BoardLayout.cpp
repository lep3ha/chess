#include "board/BoardLayout.hpp"

#include <algorithm>
#include <cmath>

#include "Config.hpp"

BoardLayout BoardLayout::fromWindowSize(sf::Vector2u size) {
    const sf::Vector2f windowSize(size);
    const float available = static_cast<float>(std::min(size.x, size.y));
    const float exactCellSize = available / (static_cast<float>(FIELD_SIDE) + 2.0F / 3.0F);
    // Retain the original 15-pixel steps, but also fit very small windows.
    const float steppedCellSize = std::floor(exactCellSize / 15.0F) * 15.0F;
    const float length = steppedCellSize > 0.0F ? steppedCellSize : exactCellSize;
    const sf::Vector2f cellSize(length, length);
    const sf::Vector2f borderThickness = cellSize / 3.0F;
    const sf::Vector2f borderSize = cellSize * static_cast<float>(FIELD_SIDE) + borderThickness * 2.0F;
    return {windowSize, cellSize, borderSize, borderThickness, (windowSize - borderSize) / 2.0F};
}
