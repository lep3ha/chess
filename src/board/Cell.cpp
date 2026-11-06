#include "board/Cell.hpp"

void Cell::setCoordinates(sf::Vector2i coordinates) { m_coordinates = coordinates; }

sf::Vector2i Cell::getCoordinates() const { return m_coordinates; }
