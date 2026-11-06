#include "app/GameWindow.hpp"

GameWindow::GameWindow(sf::VideoMode mode, const sf::String &title) : sf::RenderWindow(mode, title) { onResize(); }

void GameWindow::onResize() {
    const auto size = getSize();
    if (size.x == 0 || size.y == 0) {
        return;
    }
    m_layout = BoardLayout::fromWindowSize(size);
    setView(sf::View(m_layout.windowSize / 2.0F, m_layout.windowSize));
}

const BoardLayout &GameWindow::getLayout() const { return m_layout; }
