#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
protected:
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;

public:
    using ChessPiece::ChessPiece;
    vector<ChessMove> capturingMoves() override;
    vector<ChessMove> nonCapturingMoves() override;
};

#endif //PAWN_H