#ifndef BOARD_LAYOUT_HPP
#define BOARD_LAYOUT_HPP

#include <SFML/System/Vector2.hpp>

struct BoardLayout {
    sf::Vector2f windowSize;
    sf::Vector2f cellSize;
    sf::Vector2f borderSize;
    sf::Vector2f borderThickness;
    sf::Vector2f fieldStart;

    static BoardLayout fromWindowSize(sf::Vector2u size);
};

#endif
