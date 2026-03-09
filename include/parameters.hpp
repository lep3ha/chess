#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <SFML/Graphics.hpp>
#define WOODEN_THEME

#if defined(WOODEN_THEME)
    #define THEME_PATH          "assets/images/themes/wooden/"
#elif defined(DEFAULT_THEME)
    #define THENE_PATH          "assets/images/themes/default/"
#endif

#define BACKGROUND_IMAGE_PATH   THEME_PATH"backgroundImage.png"
#define BLACK_KING_PATH         THEME_PATH"blackKing.png"
#define BLACK_QUEEN_PATH        THEME_PATH"blackQueen.png"
#define BLACK_ROOK_PATH         THEME_PATH"blackRook.png"
#define BLACK_BISHOP_PATH       THEME_PATH"blackBishop.png"
#define BLACK_KNIGHT_PATH       THEME_PATH"blackKnight.png"
#define BLACK_PAWN_PATH         THEME_PATH"blackPawn.png"
#define WHITE_KING_PATH         THEME_PATH"whiteKing.png"
#define WHITE_QUEEN_PATH        THEME_PATH"whiteQueen.png"
#define WHITE_ROOK_PATH         THEME_PATH"whiteRook.png"
#define WHITE_BISHOP_PATH       THEME_PATH"whiteBishop.png"
#define WHITE_KNIGHT_PATH       THEME_PATH"whiteKnight.png"
#define WHITE_PAWN_PATH         THEME_PATH"whitePawn.png"
#define BLACK_CELL_PATH         THEME_PATH"blackCell.png"
#define WHITE_CELL_PATH         THEME_PATH"whiteCell.png"
#define BORDER_PATH             THEME_PATH"boardBorder.png"
#define MAIN_ICON_PATH          THEME_PATH"mainIcon.png"
#define WINDOW_TITLE            "Chess Game"

constexpr unsigned int FIELD_SIDE = 8;
constexpr unsigned int ANIMATION_TIME = 10; // required number of frames per animation
constexpr unsigned short int FRAMERATE_LIMIT = 60;
sf::Vector2f WINDOW_SIZE;
sf::Vector2f BORDER_SIZE;
sf::Vector2f CELL_SIZE;
sf::Vector2f FIELD_START;
sf::Vector2f BORDER_THICKNESS;

enum class PieceType {
    KING,
    QUEEN,
    ROOK, 
    BISHOP,
    KNIGHT,
    PAWN,
    NONE  
};

#define BLACK (-1)
#define WHITE (1)
#define EMPTY (0)
#define BOTH_SIDES (-11)

enum MovementType { 
    DEFAULT, 
    CAPTURE, 
    SHORT_CASTLING, 
    LONG_CASTLING, 
    EN_PASSANT, 
    PROMOTION 
};

#endif  /* PARAMETERS_HPP */