#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "ChessBoard.h"
#include <vector>
#include "ChessMove.h"
#include "ChessPiece.h"
#include <random>

class ChessAI {
public:
    virtual ChessMove getMove(ChessBoard& board, bool is_white) = 0;
    virtual ~ChessAI() {}

    ChessMove promote_pawn(ChessBoard& board, const ChessMove& move, char promotion_piece);

protected:
    template<typename T>
    T random_element(const vector<T>& vec) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, vec.size() - 1);
        return vec[dist(gen)];
    }

};

#endif // CHESS_AI_H