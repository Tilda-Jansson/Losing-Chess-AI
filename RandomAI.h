#ifndef CHESS_RANDOMAI_H
#define CHESS_RANDOMAI_H

#include "ChessAI.h"

class RandomAI : virtual public ChessAI {
public:
    ChessMove CheckPawnPromotionRandom(ChessBoard& board, const ChessMove& move, bool is_white);
    ChessMove getMove(ChessBoard& board, bool is_white) override;
};

#endif // CHESS_RANDOMAI_H