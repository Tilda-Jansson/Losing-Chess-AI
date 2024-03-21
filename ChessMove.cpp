#include "ChessMove.h"

bool ChessMove::operator==(const ChessMove& other) const {
    return from_x == other.from_x &&
           from_y == other.from_y &&
           to_x == other.to_x &&
           to_y == other.to_y &&
           piece == other.piece;
}
