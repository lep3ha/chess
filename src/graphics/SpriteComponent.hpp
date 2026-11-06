#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "graphics/IRenderableComponent.hpp"

// A sprite refers to its own texture, so copying or moving it is unsafe.
class SpriteComponent : public IRenderableComponent {
  protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

  public:
    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent &) = delete;
    SpriteComponent &operator=(const SpriteComponent &) = delete;
    SpriteComponent(SpriteComponent &&) = delete;
    SpriteComponent &operator=(SpriteComponent &&) = delete;

    bool isContains(sf::Vector2i point) const override;
    void render(sf::RenderWindow &renderWindow) const override;
    void initWithPath(const std::string &texturePath);
    sf::Vector2f getPosition() const override;
    void setPosition(sf::Vector2f newPosition) override;
    void setScale(sf::Vector2f scale) override;
    void setSize(sf::Vector2f newSize) override;
};

#endif
