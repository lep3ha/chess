cmake_minimum_required(VERSION 3.16)
project(ChessGame VERSION 0.1.0 LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Use an out-of-source build: cmake -S . -B build")
endif()

# The project uses the SFML 2 API. SFML 3 is not source-compatible.
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(CMAKE_CXX_EXTENSIONS OFF)

function(chess_target_options target)
    target_compile_features(${target} PUBLIC cxx_std_17)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

# Copy assets to the build tree and track changes to the source images.
file(GLOB_RECURSE CHESS_ASSETS CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
foreach(asset IN LISTS CHESS_ASSETS)
    configure_file("assets/${asset}" "assets/${asset}" COPYONLY)
endforeach()

add_library(chess_core STATIC
    src/app/Game.cpp
    src/app/GameWindow.cpp
    src/board/Board.cpp
    src/board/BoardLayout.cpp
    src/board/BoardModel.cpp
    src/board/Cell.cpp
    src/graphics/Assets.cpp
    src/graphics/MovableSpriteComponent.cpp
    src/graphics/SpriteComponent.cpp
    src/pieces/Bishop.cpp
    src/pieces/King.cpp
    src/pieces/Knight.cpp
    src/pieces/Movement.cpp
    src/pieces/Pawn.cpp
    src/pieces/Piece.cpp
    src/pieces/Queen.cpp
    src/pieces/Rook.cpp
)
target_include_directories(chess_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(chess_core PUBLIC sfml-graphics sfml-window sfml-system)
target_compile_definitions(chess_core PRIVATE CHESS_ASSET_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}/assets")
chess_target_options(chess_core)

add_executable(ChessGame src/main.cpp)
target_link_libraries(ChessGame PRIVATE chess_core)
chess_target_options(ChessGame)

include(CTest)
if(BUILD_TESTING)
    add_executable(model_tests tests/model_tests.cpp)
    target_link_libraries(model_tests PRIVATE chess_core)
    chess_target_options(model_tests)
    add_test(NAME model_tests COMMAND model_tests)

    add_executable(graphics_tests tests/graphics_tests.cpp)
    target_link_libraries(graphics_tests PRIVATE chess_core)
    chess_target_options(graphics_tests)
    add_test(NAME graphics_tests COMMAND graphics_tests)
    set_tests_properties(graphics_tests PROPERTIES LABELS "graphics" TIMEOUT 30)
endif()
