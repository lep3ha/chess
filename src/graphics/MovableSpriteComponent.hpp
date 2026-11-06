#ifndef MOVABLE_SPRITE_COMPONENT_HPP
#define MOVABLE_SPRITE_COMPONENT_HPP

#include "graphics/SpriteComponent.hpp"

class MovableSpriteComponent : public SpriteComponent {
  public:
    void shift(sf::Vector2f delta);
};

#endif
