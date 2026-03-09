#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

#include "parameters.hpp"
#include "SpriteComponent.hpp"

class Cell : public SpriteComponent {
private:
    sf::Vector2i m_coordinates;
public:
    void setCoordinates(sf::Vector2i coordinates);
    sf::Vector2i getCoordinates();
    Cell& operator =(const Cell& cell);
    Cell();
    ~Cell();
};

void Cell::setCoordinates(sf::Vector2i coordinates) {
    m_coordinates = coordinates;
}

sf::Vector2i Cell::getCoordinates() {
    return m_coordinates;
}

Cell& Cell::operator =(const Cell& cell) {
    if (this != &cell) {
        this->m_coordinates = cell.m_coordinates;
    }
    return *this;
}

Cell::Cell() : SpriteComponent() {

}
Cell::~Cell() {

}

#endif  /* CELL_HPP */