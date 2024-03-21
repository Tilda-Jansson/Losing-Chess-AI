#include "RandomAI.h"

ChessMove RandomAI::CheckPawnPromotionRandom(ChessBoard& board, const ChessMove& move, bool is_white){
    size_t rows = board.getRows() - 1;
    if ((!is_white && move.to_x == rows) || (is_white && move.to_x == 0)) {
            if (move.piece->getLatin1Representation() == (is_white ? 'P' : 'p')) {
                // Random promotion piece
                vector<char> promotion_pieces = {'K', 'Q', 'R', 'B', 'N'};
                ChessMove promoted_move = promote_pawn(board, move, random_element(promotion_pieces));
                
                // Remove the pawn and add the promoted piece to the respective pieces list
                board.updatePieceLists(move.piece, promoted_move.piece);
                board.setPieceAt(promoted_move.from_x, promoted_move.from_y, promoted_move.piece);
                return promoted_move;
            }
    }
    return move;
}


ChessMove RandomAI::getMove(ChessBoard & board, bool is_white) {
    vector<ChessMove> capturing_moves = board.capturingMoves(is_white);
    vector<ChessMove> non_capturing_moves = board.nonCapturingMoves(is_white);

    // If there are capturing moves, perform one at random
    if (!capturing_moves.empty()) {
        ChessMove random_capturing_move = random_element(capturing_moves);
        return CheckPawnPromotionRandom(board, random_capturing_move, is_white);
    }

    // If there are no capturing moves, perform a non-capturing move at random
    if (!non_capturing_moves.empty()) {
        ChessMove random_non_capturing_move = random_element(non_capturing_moves);
        return CheckPawnPromotionRandom(board, random_non_capturing_move, is_white);
    }

    // If no moves are possible, return an empty move
    return ChessMove(-1, -1, -1, -1, nullptr);
}