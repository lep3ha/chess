#ifndef CELL_HPP
#define CELL_HPP

#include "graphics/SpriteComponent.hpp"

class Cell : public SpriteComponent {
  private:
    sf::Vector2i m_coordinates{};

  public:
    void setCoordinates(sf::Vector2i coordinates);
    sf::Vector2i getCoordinates() const;
};

#endif
