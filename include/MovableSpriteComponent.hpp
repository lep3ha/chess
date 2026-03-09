#ifndef MOVABLE_SPRITE_COMPONENT_HPP
#define MOVABLE_SPRITE_COMPONENT_HPP

#include "SpriteComponent.hpp"

class MovableSpriteComponent : public SpriteComponent{
private:
    bool isInAction = false;

public:
    void shift(sf::Vector2f delta);
    MovableSpriteComponent();
    virtual ~MovableSpriteComponent();

};

void MovableSpriteComponent::shift(sf::Vector2f delta) {
    m_sprite.move(delta);
}

MovableSpriteComponent::MovableSpriteComponent() : SpriteComponent() {}

MovableSpriteComponent::~MovableSpriteComponent() {}

#endif /* MOVABLE_SPRITE_COMPONENT_HPP */