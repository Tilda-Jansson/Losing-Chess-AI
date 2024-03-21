#include "King.h"

int King::validMove(int to_x, int to_y) {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();
    
    // Check if position is within board boundaries
    if (to_x < 0 || to_x >= rows || to_y < 0 || to_y >= cols) {
        return 0;
    }

    int drow = abs(to_x - m_x);
    int dcol = abs(to_y - m_y);
    if (drow * dcol == 1 || drow + dcol == 1) {
        if (m_board->isEmpty(to_x, to_y)) {
            return 1;
        } else if (m_board->isOpponent(to_x, to_y, m_is_white)) {
            return 2;
        }
    }

    return 0;
}


char32_t King::utfRepresentation() {
    return m_is_white ? U'\u265A' : U'\u2654';
}

char King::latin1Representation() {
    return m_is_white ? 'K' : 'k';
}


vector<ChessMove> King::capturingMoves() {
    vector<ChessMove> moves;
    for (int drow = -1; drow <= 1; ++drow) {
        for (int dcol = -1; dcol <= 1; ++dcol) {
            if (drow == 0 && dcol == 0) {
                continue;
            }
            int x = m_x + drow;
            int y = m_y + dcol;

            if (capturingMove(x, y)) {
                moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));
            }
        }
    }
    return moves;
}

vector<ChessMove> King::nonCapturingMoves() {
    vector<ChessMove> moves;
    for (int drow = -1; drow <= 1; ++drow) {
        for (int dcol = -1; dcol <= 1; ++dcol) {
            if (drow == 0 && dcol == 0) {
                continue;
            }
            int x = m_x + drow;
            int y = m_y + dcol;

            if (nonCapturingMove(x, y)) {
                moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));
            }
        }
    }

    return moves;
}
