#include "pieces/Movement.hpp"

bool Movement::operator==(const Movement &move) const {
    return type == move.type && toCellCoordinates == move.toCellCoordinates &&
           fromCellCoordinates == move.fromCellCoordinates;
}
