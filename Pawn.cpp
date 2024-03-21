#include "Pawn.h"

int Pawn::validMove(int to_x, int to_y) {
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();

    if (to_x < 0 || to_x >= rows || to_y < 0 || to_y >= cols) {
        return 0;
    }

    int drow = m_is_white ? -1 : 1;
    if (m_y == to_y && m_x + drow == to_x) {
        if (m_board->isEmpty(to_x, to_y))
            return 1;
    } 
    else if (abs(m_y - to_y) == 1 && m_x + drow == to_x) {
        if (m_board->isOpponent(to_x, to_y, m_is_white)) {
                return 2;
        }
    }

    else if ((m_is_white && m_x == (rows-2)) || (!m_is_white && m_x == 1)) {
        if (m_y == to_y && m_x + 2 * drow == to_x){
            
            int x = m_x + drow;
            while (x != to_x) {
                if (!m_board->isEmpty(x, m_y)) {
                    return 0;
                }
                x += drow;
            }

            if (m_board->isEmpty(to_x, to_y)){
                return 1;
            }
        }
    }

    return 0;
}


char32_t Pawn::utfRepresentation() {
    return m_is_white ? U'\u265F' : U'\u2659';
}

char Pawn::latin1Representation() {
    return m_is_white ? 'P' : 'p';
}

vector<ChessMove> Pawn::capturingMoves() {
    vector<ChessMove> moves;
    int drow = m_is_white ? -1 : 1;

    for (int dcol = -1; dcol <= 1; dcol += 2) {
        int x = m_x + drow;
        int y = m_y + dcol;
        if (capturingMove(x, y))
            moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));

    }

    return moves;
}

vector<ChessMove> Pawn::nonCapturingMoves() {
    vector<ChessMove> moves;
    size_t rows = m_board->getRows();
    size_t cols = m_board->getCols();

    int drow = m_is_white ? -1 : 1;

    int x = m_x + drow;
    int y = m_y;
    if (nonCapturingMove(x, y))
        moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));

    if ((m_is_white && m_x == (rows-2)) || (!m_is_white && m_x == 1)) {
        x = m_x + 2 * drow;
        
        if (nonCapturingMove(x, y))
            moves.push_back(ChessMove(m_x, m_y, x, y, shared_from_this()));
    }

    return moves;
}





