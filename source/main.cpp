#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
    GameWindow renderWindow(sf::VideoMode::getDesktopMode(), WINDOW_TITLE);
    renderWindow.setFramerateLimit(FRAMERATE_LIMIT);
    renderWindow.setVerticalSyncEnabled(true);
    sf::Image mainIcon;
    mainIcon.loadFromFile(MAIN_ICON_PATH);
    renderWindow.setIcon(256, 256, mainIcon.getPixelsPtr());
    Game game;
    game.play(renderWindow);
    return 0;
}