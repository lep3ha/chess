#include <SFML/Graphics/Image.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "Config.hpp"
#include "app/Game.hpp"
#include "graphics/Assets.hpp"

int main() {
#if defined(__linux__)
    // SFML 2 aborts instead of throwing when no X11 display is available.
    const char *display = std::getenv("DISPLAY");
    if (display == nullptr || display[0] == '\0') {
        std::cerr << "Chess Game: DISPLAY is not set. Run from a graphical desktop or use SSH X11 forwarding.\n"
                     "For automated tests without a desktop: xvfb-run -a ctest --test-dir build --output-on-failure\n";
        return 1;
    }
#endif
    try {
        GameWindow renderWindow(sf::VideoMode::getDesktopMode(), WINDOW_TITLE);
        renderWindow.setFramerateLimit(FRAMERATE_LIMIT);
        sf::Image mainIcon;
        const std::string iconPath = assetPath(MAIN_ICON_PATH);
        if (!mainIcon.loadFromFile(iconPath)) {
            throw std::runtime_error("Cannot load window icon: " + iconPath);
        }
        const auto iconSize = mainIcon.getSize();
        renderWindow.setIcon(iconSize.x, iconSize.y, mainIcon.getPixelsPtr());
        Game game(renderWindow.getLayout());
        game.play(renderWindow);
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "Chess Game: " << error.what() << '\n';
        return 1;
    }
}
