#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <SFML/System/Vector2.hpp>

#include "Config.hpp"

struct Movement {
    MovementType type = DEFAULT;
    sf::Vector2i toCellCoordinates{};
    sf::Vector2i fromCellCoordinates{};

    bool operator==(const Movement &move) const;
};

#endif
