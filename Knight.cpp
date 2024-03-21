#include "Knight.h"

int Knight::validMove(int to_x, int to_y) {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();

    // Check if position is within board boundaries
    if (to_x < 0 || to_x >= rows || to_y < 0 || to_y >= cols) {
        return 0;
    }
    
    int drow = abs(to_x - m_x);
    int dcol = abs(to_y - m_y);

    if ((drow == 2 && dcol == 1) || (drow == 1 && dcol == 2)) {
        if (m_board->isEmpty(to_x, to_y)) {
            return 1;
        } else if (m_board->isOpponent(to_x, to_y, m_is_white)) {
            return 2;
        }
    }
    return 0;
}

char32_t Knight::utfRepresentation() {
    return m_is_white ? U'\u265E' : U'\u2658';
}

char Knight::latin1Representation() {
    return m_is_white ? 'N' : 'n';
}

vector<ChessMove> Knight::capturingMoves() {
    vector<ChessMove> moves;

    for (int drow = -2; drow <= 2; drow++) {
        if (drow == 0) continue;
        int dcol = 3 - abs(drow);
        if (capturingMove(m_x + drow, m_y + dcol)) {
            moves.push_back(ChessMove(m_x, m_y, m_x + drow, m_y + dcol, shared_from_this()));
        }
        if (capturingMove(m_x + drow, m_y - dcol)) {
            moves.push_back(ChessMove(m_x, m_y, m_x + drow, m_y - dcol, shared_from_this()));
        }
    }
    return moves;
}

vector<ChessMove> Knight::nonCapturingMoves() {
    vector<ChessMove> moves;

    for (int drow = -2; drow <= 2; drow++) {
        if (drow == 0) continue;
        int dcol = 3 - abs(drow);
        if (nonCapturingMove(m_x + drow, m_y + dcol)) {
            moves.push_back(ChessMove(m_x, m_y, m_x + drow, m_y + dcol, shared_from_this()));
        }
        if (nonCapturingMove(m_x + drow, m_y - dcol)) {
            moves.push_back(ChessMove(m_x, m_y, m_x + drow, m_y - dcol, shared_from_this()));
        }
    }

    return moves;
}
