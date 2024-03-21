#include "ChessBoard.h"
#include "King.h" //
#include "Queen.h" //
#include "Rook.h"  //
#include "Bishop.h" //
#include "Knight.h" //
#include "Pawn.h" //
#include <locale>
#include <codecvt>

ChessBoard::ChessBoard(size_t rows, size_t cols) 
            : m_rows(rows), m_cols(cols) {}

 
void ChessBoard::movePiece(ChessMove chess_move) {
    shared_ptr<ChessPiece> captured_piece = getPieceAt(chess_move.to_x, chess_move.to_y);

    // Check if a piece was captured
    if (captured_piece != nullptr) {
        // Remove the captured piece from the vector
        auto it = find(m_pieces.begin(), m_pieces.end(), captured_piece);
        if (it != m_pieces.end()) {
            m_pieces.erase(it);
        }
    }

    // Update the piece position
    chess_move.piece->setX(chess_move.to_x);
    chess_move.piece->setY(chess_move.to_y);
}


vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    vector<ChessMove> moves;

    for (const auto &piece : m_pieces) {
        // If the piece color is the same as 'is_white'
        if (piece->isWhite() == is_white) {
            vector<ChessMove> pieceMoves = piece->capturingMoves();
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    return moves;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    vector<ChessMove> moves;

    for (const auto &piece : m_pieces) {
        // If the piece color is the same as 'is_white'
        if (piece->isWhite() == is_white) {
            vector<ChessMove> pieceMoves = piece->nonCapturingMoves();
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }

    return moves;
}


ChessBoard & operator>>(istream & is, ChessBoard & cb) {
    vector<string> lines;
    string line;

    while (getline(is, line)) {
        if (!line.empty()) { 
            lines.push_back(line);
        } else {
            break;
        }
    }
    
    if (lines.size() == 0) {
        throw runtime_error("Invalid input: The input file is empty.");
    }

    size_t rows = lines.size();
    size_t cols = lines[0].size();
    
    //cerr << rows << endl;
    //cerr << cols << endl;

    if (cols == 0) {
        throw runtime_error("Invalid input: The lines in the input file are empty.");
    }

    cb = ChessBoard(rows, cols); 

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            char ch = lines[row][col];
            shared_ptr<ChessPiece> piece;
            switch (ch) {
                case 'R': piece = make_shared<Rook>(row, col, true, &cb); break;
                case 'N': piece = make_shared<Knight>(row, col, true, &cb); break;
                case 'B': piece = make_shared<Bishop>(row, col, true, &cb); break;
                case 'Q': piece = make_shared<Queen>(row, col, true, &cb); break;
                case 'K': piece = make_shared<King>(row, col, true, &cb); break; 
                case 'P': piece = make_shared<Pawn>(row, col, true, &cb); break;
                case 'r': piece = make_shared<Rook>(row, col, false, &cb); break;
                case 'n': piece = make_shared<Knight>(row, col, false, &cb); break;
                case 'b': piece = make_shared<Bishop>(row, col, false, &cb); break;
                case 'q': piece = make_shared<Queen>(row, col, false, &cb); break;
                case 'k': piece = make_shared<King>(row, col, false, &cb); break; 
                case 'p': piece = make_shared<Pawn>(row, col, false, &cb); break;
                case '.': piece = nullptr; break;
                default: throw runtime_error("Invalid character in input");
            }

            if (piece) {
                cb.setPieceAt(row, col, piece); 
            }
        }
    }
    return cb;
}


ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    size_t rows = cb.getRows();
    size_t cols = cb.getCols();
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            shared_ptr<ChessPiece> piece = cb.getPieceAt(row, col);
            if (piece) {
                //os << piece->getUtfRepresentation();
                char32_t utfChar = piece->getUtfRepresentation();
                wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
                string utf8String = converter.to_bytes(utfChar);
                os << utf8String;

            } else {
                os << '.';
            }
        }
        os << endl;
    }
    return cb;
}


shared_ptr<ChessPiece> ChessBoard::getPieceAt(size_t row, size_t col) const {
    for (const auto& piece : m_pieces) {
        if (piece->getX() == row && piece->getY() == col) {
            return piece;
        }
    }
    return nullptr;

}

void ChessBoard::setPieceAt(size_t row, size_t col, shared_ptr<ChessPiece> piece) { 
    if (row < 0 || row >= getRows() || col < 0 || col >= getCols()) {
        throw std::out_of_range("Index out of range");
    }

    // Removing any existing piece at the given location
    auto it = std::remove_if(m_pieces.begin(), m_pieces.end(), [row, col](const auto& p) {
        return p->getX() == row && p->getY() == col;
    });
    m_pieces.erase(it, m_pieces.end());

    // Update the piece position or add it to the list if it's not there
    if (piece != nullptr) {
        piece->setX(row);
        piece->setY(col);

        auto piece_it = std::find(m_pieces.begin(), m_pieces.end(), piece);
        if (piece_it == m_pieces.end()) { // If the piece is not already in the list
            m_pieces.push_back(piece);    // Add it to the list
        }
    }
}


bool ChessBoard::isEmpty(int x, int y) const {
    return getPieceAt(x, y) == nullptr;
}

bool ChessBoard::isOpponent(int x, int y, bool is_white) const {
    shared_ptr<ChessPiece> piece = getPieceAt(x, y);
    return piece && piece->isWhite() != is_white;
}

void ChessBoard::addPiece(shared_ptr<ChessPiece> piece) {
    m_pieces.push_back(piece);
}

vector<shared_ptr<ChessPiece>> ChessBoard::getPieces(bool is_white) const {
    vector<shared_ptr<ChessPiece>> result;
    for (const auto &piece : m_pieces) {
        if (piece->isWhite() == is_white) {
            result.push_back(piece);
        }
    }
    return result;
}



bool ChessBoard::gameOver(bool is_white){
    const vector<shared_ptr<ChessPiece>> &pieces = getPieces(is_white);
    bool no_remaining_pieces = pieces.size() == 0;

    vector<ChessMove> moves;
    vector<ChessMove> capturing_moves = capturingMoves(is_white);
    vector<ChessMove> non_capturing_moves = nonCapturingMoves(is_white);

    moves.insert(moves.end(), capturing_moves.begin(), capturing_moves.end());
    moves.insert(moves.end(), non_capturing_moves.begin(), non_capturing_moves.end());

    bool no_legal_moves = moves.empty();

    return no_legal_moves || no_remaining_pieces;
}

void ChessBoard::updatePieceLists(shared_ptr<ChessPiece> pawn, shared_ptr<ChessPiece> promoted_move) {
    auto& piecelist = m_pieces;
    auto it = find(piecelist.begin(), piecelist.end(), pawn);
    if (it != piecelist.end()) {
        piecelist.erase(it);
    }
    //add piece
    piecelist.push_back(promoted_move);
}

// Helper 
void ChessBoard::printPieceLists() {
    cout << "White pieces: ";
    for (const auto& piece : m_pieces) {
        if (piece->isWhite()) {
            cout << piece->getLatin1Representation() << " ";
        }
    }
    cout << endl;

    cout << "Black pieces: ";
    for (const auto& piece : m_pieces) {
        if (!piece->isWhite()) {
            cout << piece->getLatin1Representation() << " ";
        }
    }
    cout << endl;
}

size_t ChessBoard::getRows() const {
    return m_rows;
}

size_t ChessBoard::getCols() const {
    return m_cols;
}
