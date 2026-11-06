#include "graphics/Assets.hpp"

#include <filesystem>

std::string assetPath(const std::string &relativePath) {
    return (std::filesystem::path(CHESS_ASSET_DIRECTORY) / relativePath).string();
}
