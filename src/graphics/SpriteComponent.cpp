#include "graphics/SpriteComponent.hpp"

#include <stdexcept>

#include "graphics/Assets.hpp"

bool SpriteComponent::isContains(sf::Vector2i point) const {
    return m_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
}

void SpriteComponent::render(sf::RenderWindow &renderWindow) const { renderWindow.draw(m_sprite); }

void SpriteComponent::initWithPath(const std::string &texturePath) {
    if (texturePath.empty()) {
        throw std::invalid_argument("Texture path cannot be empty");
    }
    const std::string path = assetPath(texturePath);
    if (!m_texture.loadFromFile(path)) {
        throw std::runtime_error("Cannot load texture: " + path);
    }
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture, true);
}

sf::Vector2f SpriteComponent::getPosition() const { return m_sprite.getPosition(); }

void SpriteComponent::setSize(sf::Vector2f newSize) {
    const auto textureSize = m_texture.getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        throw std::logic_error("Load a texture before setting the sprite size");
    }
    setScale({newSize.x / static_cast<float>(textureSize.x), newSize.y / static_cast<float>(textureSize.y)});
}

void SpriteComponent::setPosition(sf::Vector2f newPosition) { m_sprite.setPosition(newPosition); }

void SpriteComponent::setScale(sf::Vector2f scale) { m_sprite.setScale(scale); }
