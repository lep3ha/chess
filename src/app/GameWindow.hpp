#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "board/BoardLayout.hpp"

class GameWindow : public sf::RenderWindow {
  private:
    BoardLayout m_layout{};

  protected:
    void onResize() override;

  public:
    GameWindow(sf::VideoMode mode, const sf::String &title);
    const BoardLayout &getLayout() const;
};

#endif
