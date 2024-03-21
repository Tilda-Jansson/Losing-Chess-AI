#include "ChessAI.h"
#include "King.h" 
#include "Queen.h" 
#include "Rook.h"  
#include "Bishop.h" 
#include "Knight.h" 
#include "Pawn.h"

ChessMove ChessAI::promote_pawn(ChessBoard& board, const ChessMove& move, char promotion_piece) {
    int promotion_x = move.to_x;
    int promotion_y = move.to_y;

    shared_ptr<ChessPiece> promoted_piece;
    switch (promotion_piece) {
        case 'K':
            promoted_piece = make_shared<King>(promotion_x, promotion_y, move.piece->isWhite(), &board);
            break;
        case 'Q':
            promoted_piece = make_shared<Queen>(promotion_x, promotion_y, move.piece->isWhite(), &board);
            break;
        case 'R':
            promoted_piece = make_shared<Rook>(promotion_x, promotion_y, move.piece->isWhite(), &board);
            break;
        case 'B':
            promoted_piece = make_shared<Bishop>(promotion_x, promotion_y, move.piece->isWhite(), &board);
            break;
        case 'N':
            promoted_piece = make_shared<Knight>(promotion_x, promotion_y, move.piece->isWhite(), &board);
            break;
    }

    return ChessMove(move.from_x, move.from_y, promotion_x, promotion_y, promoted_piece);
}