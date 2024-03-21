#include "Queen.h"


int Queen::validMove(int to_x, int to_y) {
    int bishopValidMove = Bishop::validMove(to_x, to_y);
    int rookValidMove = Rook::validMove(to_x, to_y);

    if (bishopValidMove != 0) {
        return bishopValidMove;
    }
    return rookValidMove;
}

char32_t Queen::utfRepresentation() {
    return m_is_white ? U'\u265B' : U'\u2655';
}

char Queen::latin1Representation() {
    return m_is_white ? 'Q' : 'q';
}

vector<ChessMove> Queen::capturingMoves() {
    vector<ChessMove> moves;

    // Combine Rook's capturing moves
    vector<ChessMove> rookCapturingMoves = Rook::capturingMoves();
    moves.insert(moves.end(), rookCapturingMoves.begin(), rookCapturingMoves.end());

    // Combine Bishop's capturing moves
    vector<ChessMove> bishopCapturingMoves = Bishop::capturingMoves();
    moves.insert(moves.end(), bishopCapturingMoves.begin(), bishopCapturingMoves.end());

    return moves;
}


vector<ChessMove> Queen::nonCapturingMoves() {
    vector<ChessMove> moves;
    // Combine Rook's non-capturing moves
    vector<ChessMove> rookNonCapturingMoves = Rook::nonCapturingMoves();
    moves.insert(moves.end(), rookNonCapturingMoves.begin(), rookNonCapturingMoves.end());

    // Combine Bishop's non-capturing moves
    vector<ChessMove> bishopNonCapturingMoves = Bishop::nonCapturingMoves();
    moves.insert(moves.end(), bishopNonCapturingMoves.begin(), bishopNonCapturingMoves.end());

    return moves;
}