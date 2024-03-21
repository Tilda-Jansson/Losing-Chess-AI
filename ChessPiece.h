#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include "ChessBoard.h"
#include "ChessMove.h"

using namespace std;

class ChessPiece : public enable_shared_from_this<ChessPiece>{
    friend void ChessBoard::movePiece(ChessMove chess_move);
    
protected:                               
    int m_x, m_y; // row , col
    bool m_is_white;
    ChessBoard* m_board;
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    virtual int validMove(int to_x, int to_y) = 0;
    virtual char32_t utfRepresentation() = 0;
    virtual char latin1Representation() = 0;

public:
    // Constructor
    ChessPiece(int x, int y, bool is_white, ChessBoard * board);

    virtual ~ChessPiece() {};
    /**
     * Checks if this move is valid for this piece and captures
     * a piece of the opposite color.
     */
    bool capturingMove(int to_x, int to_y);
    /**
     * Checks if this move is valid but does not capture a piece.
     */
    bool nonCapturingMove(int to_x, int to_y);
    virtual vector<ChessMove> capturingMoves() = 0;
    virtual vector<ChessMove> nonCapturingMoves() = 0;

    int getX() const;
    int getY() const;
    bool isWhite() const;
    ChessBoard* getBoard() const;
    void setX(int x);
    void setY(int y);
    void setBoard(ChessBoard* board);

    char getLatin1Representation();
    char32_t getUtfRepresentation();
};


#endif //CHESSPIECE_H
