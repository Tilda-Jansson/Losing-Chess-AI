#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include "ChessMove.h"
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class ChessPiece;

class ChessBoard {
private:
    vector<shared_ptr<ChessPiece>> m_pieces;
    size_t m_rows, m_cols;
    //vector<shared_ptr<ChessPiece>> m_white_pieces;
    //vector<shared_ptr<ChessPiece>> m_black_pieces;

public:
    ChessBoard(size_t rows = 8, size_t cols = 8); 

    void movePiece(ChessMove chess_move);

    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);

    void setPieceAt(size_t row, size_t col, shared_ptr<ChessPiece> piece);
    shared_ptr<ChessPiece> getPieceAt(size_t row, size_t col) const;
    bool isEmpty(int x, int y) const;
    bool isOpponent(int x, int y, bool is_white) const;

    void addPiece(shared_ptr<ChessPiece> piece);

    void updatePieceLists(shared_ptr<ChessPiece> pawn, shared_ptr<ChessPiece> promoted_move);

    vector<shared_ptr<ChessPiece>> getPieces(bool is_white) const;

    bool gameOver(bool is_white);

    void printPieceLists();

    size_t getRows() const;
    size_t getCols() const;

};

ChessBoard & operator>>(istream & is, ChessBoard & cb);
ChessBoard & operator<<(ostream & os, ChessBoard & cb);

#endif //CHESSBOARD_H
