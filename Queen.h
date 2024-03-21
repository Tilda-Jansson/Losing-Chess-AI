#ifndef QUEEN_H
#define QUEEN_H

#include "Bishop.h"
#include "Rook.h"
#include "ChessBoard.h"

class Queen : public Bishop, public Rook {
protected:
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;

public:
    // Define the constructor for Queen
    Queen(int x, int y, bool is_white, ChessBoard* board) 
    : ChessPiece(x, y, is_white, board), Bishop(x, y, is_white, board), Rook(x, y, is_white, board) {}

    vector<ChessMove> capturingMoves() override;
    vector<ChessMove> nonCapturingMoves() override;
};

#endif //QUEEN_H
