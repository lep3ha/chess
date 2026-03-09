#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <string>
#include <iostream>

#include "IRenderableComponent.hpp"


class SpriteComponent : public IRenderableComponent {
protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
public:
    bool isContains(sf::Vector2i point) const override;
    void render(sf::RenderWindow &renderWindow) const override;
    void initWithPath(const std::string texturePath);

    // get methods
    sf::Vector2f getPosition() const override;

    // set methods
    void setPosition(sf::Vector2f newPosition) override;
    void setScale(sf::Vector2f scale) override;
    virtual void setSize(sf::Vector2f newSize) override;
    
    SpriteComponent();
    virtual ~SpriteComponent();

};
bool SpriteComponent::isContains(sf::Vector2i point) const {
    return m_sprite.getGlobalBounds().contains(point.x, point.y);
}

void SpriteComponent::render(sf::RenderWindow &renderWindow) const {
    renderWindow.draw(m_sprite);
}

void SpriteComponent::initWithPath(const std::string texturePath) {
    if (texturePath != "") { 
        if (!m_texture.loadFromFile(texturePath)) {
            std::cout << "SpriteComponent::initWithPath(const std::string texturePath): Error with open the file\n";
            std::exit(-1);
        }
        m_texture.setSmooth(true);
        m_sprite.setTexture(m_texture);
    }
    else {
        std::cout << "SpriteComponent::initWithPath(const std::string texturePath): Path can't be an empty string\n";
        std::exit(-1);
    }
}

sf::Vector2f SpriteComponent::getPosition() const {
    return m_sprite.getPosition();
}

void SpriteComponent::setSize(sf::Vector2f newSize) {
    this->setScale(sf::Vector2f(newSize.x / m_texture.getSize().x, newSize.y / m_texture.getSize().y));
}

void SpriteComponent::setPosition(sf::Vector2f newPosition) {
    m_sprite.setPosition(newPosition);
}

void SpriteComponent::setScale(sf::Vector2f scale) {
    m_sprite.setScale(scale);
}


SpriteComponent::SpriteComponent() {}

SpriteComponent::~SpriteComponent() {}

#endif  /* SPRITE_COMPONENT_HPP */