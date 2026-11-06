#include "graphics/MovableSpriteComponent.hpp"

void MovableSpriteComponent::shift(sf::Vector2f delta) { m_sprite.move(delta); }
