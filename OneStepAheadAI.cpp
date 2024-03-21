#include "OneStepAheadAI.h"

bool OneStepAheadAI::forces_capture(const ChessMove &move, ChessBoard &board, bool is_white) {
    // Store the captured piece and its position before making the move
    shared_ptr<ChessPiece> captured_piece = board.getPieceAt(move.to_x, move.to_y);
    int captured_piece_x = move.to_x;
    int captured_piece_y = move.to_y;

    // Make the move and check if it forces the opponent to capture
    // Update the board state

    // need to save the captured piece before overwriting it

    board.setPieceAt(move.to_x, move.to_y, board.getPieceAt(move.from_x, move.from_y));
 
    //board.setPieceAt(move.from_x, move.from_y, nullptr); // fail    

    // Update the piece position
    //move.piece->setX(move.to_x);
    //move.piece->setY(move.to_y);
    
    bool has_forced_capture = false;
    
    // check if any of the opponents capturing moves will capture the current captuing piece that just moved
    for(ChessMove capMove : board.capturingMoves(!is_white)){
        if (capMove.to_x == move.to_x && capMove.to_y == move.to_y){
            has_forced_capture = true;
        }

    }
    
    // Move the piece back to its original position
    board.movePiece(ChessMove(move.to_x, move.to_y, move.from_x, move.from_y, move.piece));

    // Restore the captured piece if there was one
    if (captured_piece != nullptr) {
        board.setPieceAt(captured_piece_x, captured_piece_y, captured_piece);
    }

    return has_forced_capture;
}


bool OneStepAheadAI::forces_capture_PawnPromotion(const ChessMove &move, const ChessMove &promoted_move, ChessBoard &board) {
    board.setPieceAt(promoted_move.from_x, promoted_move.from_y, promoted_move.piece);

    // Want to pick a piece that cannot capture!
    // Perform the same update, but only check capturing moves for the promoted piece:

    // Store the captured piece and its position before making the move
    shared_ptr<ChessPiece> captured_piece = board.getPieceAt(promoted_move.to_x, promoted_move.to_y);
    int captured_piece_x = promoted_move.to_x;
    int captured_piece_y = promoted_move.to_y;

    // Update the board state
    board.setPieceAt(promoted_move.to_x, promoted_move.to_y, board.getPieceAt(promoted_move.from_x, promoted_move.from_y));
    board.setPieceAt(promoted_move.from_x, promoted_move.from_y, nullptr);

    // Update the piece position
    promoted_move.piece->setX(promoted_move.to_x);
    promoted_move.piece->setY(promoted_move.to_y);
    
    // Check if the new promoted piece has to capture on its next move 
    bool has_forced_capture = !promoted_move.piece->capturingMoves().empty();

    // Move the piece back to its original position
    board.movePiece(ChessMove(promoted_move.to_x, promoted_move.to_y, promoted_move.from_x, promoted_move.from_y, promoted_move.piece));

    // Restore the captured piece if there was one
    if (captured_piece != nullptr) {
        board.setPieceAt(captured_piece_x, captured_piece_y, captured_piece);
    }
    
    board.setPieceAt(move.from_x, move.from_y, move.piece);
    
    return has_forced_capture;
}



ChessMove OneStepAheadAI::CheckPawnPromotionAhead(ChessBoard& board, const ChessMove& move, bool is_white){
    size_t rows = board.getRows() - 1;
    if ((!is_white && move.to_x == rows) || (is_white && move.to_x == 0)) {
        if (move.piece->getLatin1Representation() == (is_white ? 'P' : 'p')) {
            
            // Pick a piece that cannot capture on its next move, or promote to a random piece
            vector<char> promotion_pieces = {'K', 'Q', 'R', 'B', 'N'};
            for (char promotion_piece : promotion_pieces) {
                ChessMove promoted_move = promote_pawn(board, move, promotion_piece);
                //cout << "im i tt" << endl;
                if (!forces_capture_PawnPromotion(move, promoted_move, board)) {
                    // Remove the pawn and add the promoted piece to the respective pieces list
                    board.updatePieceLists(move.piece, promoted_move.piece);
                    board.setPieceAt(promoted_move.from_x, promoted_move.from_y, promoted_move.piece);
                    return promoted_move;
                }
            
            }
            ChessMove promoted_move = promote_pawn(board, move, random_element(promotion_pieces));
            board.updatePieceLists(move.piece, promoted_move.piece);
            board.setPieceAt(promoted_move.from_x, promoted_move.from_y, promoted_move.piece);
            return promoted_move;
        }
    }

    return move;
}


ChessMove OneStepAheadAI::getMove(ChessBoard& board, bool is_white) {
    vector<ChessMove> capturing_moves = board.capturingMoves(is_white);
    vector<ChessMove> non_capturing_moves = board.nonCapturingMoves(is_white);
    

    //cout << capturing_moves.size() << endl;
    //cout << non_capturing_moves.size() << endl;

    // If there are capturing moves, find one that forces opponent to capture, otherwise play random capturing move
    if (!capturing_moves.empty()) {
        vector<ChessMove> capturing_forcing_moves;
        for (const ChessMove& move : capturing_moves) {
            if (forces_capture(move, board, is_white)) {
                capturing_forcing_moves.push_back(move);
            }
        }

        if (!capturing_forcing_moves.empty()) {
            return CheckPawnPromotionAhead(board, random_element(capturing_forcing_moves), is_white);
        }
        return CheckPawnPromotionAhead(board, random_element(capturing_moves), is_white);
    }

    // If there are no capturing moves, find a non-capturing move that forces opponent to capture, otherwise play random non-capturing move
    vector<ChessMove> non_capturing_forcing_moves;
    for (const ChessMove& move : non_capturing_moves) {
        if (forces_capture(move, board, is_white)) {
            non_capturing_forcing_moves.push_back(move);
        }
    }
    if (!non_capturing_forcing_moves.empty()) {
        return CheckPawnPromotionAhead(board, random_element(non_capturing_forcing_moves), is_white);
    }
    if (!non_capturing_moves.empty()) {
        return CheckPawnPromotionAhead(board, random_element(non_capturing_moves), is_white);
    }

    // If no moves are possible, return an empty move
    return ChessMove(-1, -1, -1, -1, nullptr);
}
