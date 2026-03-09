#ifndef I_RENDERABLE_COMPONENT_HPP
#define I_RENDERABLE_COMPONENT_HPP

#include <SFML/Graphics.hpp>

class IRenderableComponent {
public:
    virtual bool isContains(sf::Vector2i point) const = 0;
    virtual void render(sf::RenderWindow &renderWindow) const = 0;
    virtual void setPosition(sf::Vector2f newPosition) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setScale(sf::Vector2f scale) = 0;
    virtual void setSize(sf::Vector2f newSize) = 0;
    IRenderableComponent();
    virtual ~IRenderableComponent();
};

IRenderableComponent::IRenderableComponent() {}

IRenderableComponent::~IRenderableComponent() {}

#endif /* I_RENDERABLE_COMPONENT_HPP */