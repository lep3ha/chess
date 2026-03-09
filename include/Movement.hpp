#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "Cell.hpp"
#include "parameters.hpp"

struct Movement {
    MovementType type;
    sf::Vector2i toCellCoordinates;
    sf::Vector2i fromCellCoordinates;

    bool operator ==(Movement move) {
        return ((this->type == move.type) && (move.toCellCoordinates == this->toCellCoordinates) && (move.fromCellCoordinates == this->fromCellCoordinates));
    }
};

#endif