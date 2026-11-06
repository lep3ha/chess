#include "app/Game.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game(const BoardLayout &layout) : m_board(layout) {
    m_backgroundImage.initWithPath(BACKGROUND_IMAGE_PATH);
    m_backgroundImage.setSize(layout.windowSize);
}

void Game::play(GameWindow &renderWindow) {
    while (renderWindow.isOpen()) {
        sf::Event event{};
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderWindow.close();
            } else if (event.type == sf::Event::Resized) {
                m_board.resize(renderWindow.getLayout());
                m_backgroundImage.setSize(renderWindow.getLayout().windowSize);
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                const sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
                for (int x = 0; x < FIELD_SIDE; ++x) {
                    for (int y = 0; y < FIELD_SIDE; ++y) {
                        if (m_board.getCell(x, y)->isContains(mousePosition)) {
                            std::cout << static_cast<char>('a' + x) << ' ' << y + 1 << '\n';
                        }
                    }
                }
            }
        }
        if (!renderWindow.isOpen()) {
            break;
        }
        renderWindow.clear();
        m_backgroundImage.render(renderWindow);
        m_board.render(renderWindow);
        renderWindow.display();
    }
}
