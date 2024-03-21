#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
protected:
    int validMove(int to_x, int to_y) override;
    char32_t utfRepresentation() override;
    char latin1Representation() override;

public:
    using ChessPiece::ChessPiece;
    vector<ChessMove> capturingMoves() override;
    vector<ChessMove> nonCapturingMoves() override;
};

#endif //KNIGHT_H
