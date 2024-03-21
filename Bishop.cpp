
#include "Bishop.h"

int Bishop::validMove(int to_x, int to_y) {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();
    // Check if position is within board boundaries
    if (to_x < 0 || to_x >= rows || to_y < 0 || to_y >= cols) {
        return 0;
    }

    int drow = abs(to_x - m_x);
    int dcol = abs(to_y - m_y);

    if (drow == dcol) {
        // Make sure no piece is blocking the path
        int rowDir = to_x - m_x > 0 ? 1 : -1;
        int colDir = to_y - m_y > 0 ? 1 : -1;
        int x = m_x + rowDir;
        int y = m_y + colDir;

        while (x != to_x || y != to_y) {
            if (!m_board->isEmpty(x, y)) {
                return 0;
            }
            x += rowDir;
            y += colDir;
        }
        if (m_board->isOpponent(to_x, to_y, m_is_white)){
            return 2;
        } else if (m_board->isEmpty(to_x, to_y)) {
            return 1;
        }
    }
    return 0;
}


char32_t Bishop::utfRepresentation() {
    return m_is_white ? U'\u265D' : U'\u2657';
}


char Bishop::latin1Representation() {
    return m_is_white ? 'B' : 'b';
}

vector<ChessMove> Bishop::capturingMoves() {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();
    vector<ChessMove> moves;

    for (int rowDir = -1; rowDir <= 1; rowDir += 2) {
        for (int colDir = -1; colDir <= 1; colDir += 2) {
            int x = m_x + rowDir;
            int y = m_y + colDir;

            while (x >= 0 && x < rows && y >= 0 && y < cols) {
                if (capturingMove(x, y) && m_board->isOpponent(x, y, m_is_white)) {
                    moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));
                    break;
                } else if (nonCapturingMove(x, y)) {
                    x += rowDir;
                    y += colDir;
                } else {
                    break;
                }
            }
        }
    }

    return moves;
}


vector<ChessMove> Bishop::nonCapturingMoves() {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();
    vector<ChessMove> moves;

    for (int rowDir = -1; rowDir <= 1; rowDir += 2) {
        for (int colDir = -1; colDir <= 1; colDir += 2) {
            int x = m_x + rowDir;
            int y = m_y + colDir;

            while (x >= 0 && x < rows && y >= 0 && y < cols) {
                if (nonCapturingMove(x, y)) {
                    moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));
                    x += rowDir;
                    y += colDir;
                } else {
                    break;
                }
            }
        }
    }

    return moves;
}

