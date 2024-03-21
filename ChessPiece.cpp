#include "ChessPiece.h"


ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
: m_x(x), m_y(y), m_is_white(is_white), m_board(board) {
}

//validMove returns 2 if move captures a piece.
bool ChessPiece::capturingMove(int to_x, int to_y) {
    return validMove(to_x, to_y) == 2;
}

// Returns 1 if target square is reachable and empty.
bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    return validMove(to_x, to_y) == 1;
}

int ChessPiece::getX() const { return m_x; }

int ChessPiece::getY() const { return m_y; }

bool ChessPiece::isWhite() const { return m_is_white; }

ChessBoard* ChessPiece::getBoard() const { return m_board; }

void ChessPiece::setX(int x) { m_x = x; }

void ChessPiece::setY(int y) { m_y = y; }

void ChessPiece::setBoard(ChessBoard* board) {
    m_board = board;
}

char ChessPiece::getLatin1Representation() { return latin1Representation(); }
char32_t ChessPiece::getUtfRepresentation() { return utfRepresentation(); }