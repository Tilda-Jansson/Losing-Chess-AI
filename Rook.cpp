#include "Rook.h"

int Rook::validMove(int to_x, int to_y) {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();

    // Check if position is within board boundaries
    if (to_x < 0 || to_x >= rows || to_y < 0 || to_y >= cols) {
        return 0;
    }

    if (m_x == to_x || m_y == to_y) {
        // make sure no pieces are blocking the path
        int rowDir = m_x == to_x ? 0 : (to_x - m_x > 0 ? 1 : -1);
        int colDir = m_y == to_y ? 0 : (to_y - m_y > 0 ? 1 : -1);
        int x = m_x + rowDir;
        int y = m_y + colDir;

        while (x != to_x || y != to_y) {
            if (!m_board->isEmpty(x, y)) {
                return 0;
            }
            x += rowDir;
            y += colDir;
        }

        if (m_board->isOpponent(to_x, to_y, m_is_white)) {
            return 2;
        } else if (m_board->isEmpty(to_x, to_y)) {
            return 1;
        }
    }

    return 0;
}

char32_t Rook::utfRepresentation() {
    return m_is_white ? U'\u265C' : U'\u2656';
}

char Rook::latin1Representation() {
    return m_is_white ? 'R' : 'r';
}

vector<ChessMove> Rook::capturingMoves() {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();
    vector<ChessMove> moves;

    for (int x = 0; x < rows; ++x) {
        if (x != m_x) {
            if (capturingMove(x, m_y)) {
                moves.push_back(ChessMove(m_x, m_y, x, m_y, shared_from_this()));
            }
        }
    }

    for (int y = 0; y < cols; ++y) {
        if (y != m_y) {
            if (capturingMove(m_x, y)) {
                moves.push_back(ChessMove(m_x, m_y, m_x, y, shared_from_this()));
            }
        }
    }

    return moves;
}

vector<ChessMove> Rook::nonCapturingMoves() {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();
    vector<ChessMove> moves;

    for (int x = 0; x < rows; ++x) {
        if (x != m_x) {
            if (nonCapturingMove(x, m_y)) {
                moves.push_back(ChessMove(m_x, m_y, x, m_y, shared_from_this()));
            }
        }
    }

    for (int y = 0; y < cols; ++y) {
        if (y != m_y) {
            if (nonCapturingMove(m_x, y)) {
                moves.push_back(ChessMove(m_x, m_y, m_x, y, shared_from_this()));
            }
        }
    }

    return moves;
}
