#ifndef GAME_HPP
#define GAME_HPP

#include "app/GameWindow.hpp"
#include "board/Board.hpp"

class Game {
  private:
    Board m_board;
    SpriteComponent m_backgroundImage;

  public:
    explicit Game(const BoardLayout &layout);
    void play(GameWindow &renderWindow);
};

#endif
