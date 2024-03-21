#ifndef ONE_STEP_AHEAD_AI_H
#define ONE_STEP_AHEAD_AI_H

#include "ChessAI.h"

class OneStepAheadAI : public ChessAI {
public:
    ChessMove getMove(ChessBoard& board, bool is_white) override;
    bool forces_capture(const ChessMove &move, ChessBoard &board, bool is_white);
    ChessMove CheckPawnPromotionAhead(ChessBoard& board, const ChessMove& move, bool is_white);
    bool forces_capture_PawnPromotion(const ChessMove &move, const ChessMove &promoted_move, ChessBoard &board);
};

#endif // ONE_STEP_AHEAD_AI_H
