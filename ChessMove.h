#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <memory>

using namespace std;

class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    shared_ptr<ChessPiece> piece; // you can change the position of the chess piece with this pointer.
    
    bool operator==(const ChessMove& other) const;

    ChessMove(int from_x, int from_y, int to_x, int to_y, shared_ptr<ChessPiece> piece)
        : from_x(from_x), from_y(from_y), to_x(to_x), to_y(to_y), piece(piece) {}

};

#endif //CHESSMOVE_H
