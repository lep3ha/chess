#ifndef CHESS_CONFIG_HPP
#define CHESS_CONFIG_HPP

inline constexpr int FIELD_SIDE = 8;
inline constexpr unsigned int FRAMERATE_LIMIT = 60;
inline constexpr char WINDOW_TITLE[] = "Chess Game";
inline constexpr char BACKGROUND_IMAGE_PATH[] = "images/themes/wooden/backgroundImage.png";
inline constexpr char BLACK_CELL_PATH[] = "images/themes/wooden/blackCell.png";
inline constexpr char WHITE_CELL_PATH[] = "images/themes/wooden/whiteCell.png";
inline constexpr char BORDER_PATH[] = "images/themes/wooden/boardBorder.png";
inline constexpr char MAIN_ICON_PATH[] = "images/themes/wooden/mainIcon.png";

inline constexpr int BLACK = -1;
inline constexpr int WHITE = 1;
inline constexpr int EMPTY = 0;
inline constexpr int BOTH_SIDES = -11;

enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NONE };
enum MovementType { DEFAULT, CAPTURE, SHORT_CASTLING, LONG_CASTLING, EN_PASSANT, PROMOTION };

#endif
