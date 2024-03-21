#include <fstream>
#include "RandomAI.h"
#include "OneStepAheadAI.h"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Enter: [starting_color] [ai_type for white] [ai_type for black] [input_filename]" << endl;
    if (argc != 5) {
        cout << "You must enter four valid arguments!" << endl;
        return 1;
    }

    bool is_white = (string(argv[1]) == "white");
    string ai_type1 = argv[2];
    string ai_type2 = argv[3];

    shared_ptr<ChessAI> ai1, ai2;
    if (ai_type1 == "random") {
        ai1 = make_shared<RandomAI>();
    } else if (ai_type1 == "onestep") {
        ai1 = make_shared<OneStepAheadAI>();
    } else {
        cout << "Invalid AI type. Choose either 'random' or 'onestep'." << endl;
        return 1;
    }

    if (ai_type2 == "random") {
        ai2 = make_shared<RandomAI>();
    } else if (ai_type2 == "onestep"){
        ai2 = make_shared<OneStepAheadAI>();
    } else {
        cout << "Invalid AI type. Choose either 'random' or 'onestep'." << endl;
        return 1;
    }

    string input_filename = argv[4];
    ifstream input_file(input_filename);

    if (!input_file.is_open()) {
        cerr << "Failed to open input file: " << input_filename << endl;
        return 1;
    }

    // Read the starting board configuration
    ChessBoard board;
    try {
        input_file >> board;
    } catch (std::runtime_error &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }
    input_file.close();

    cout << "starting board configuration" << endl;
    cout << board;
    // Print the updated piece lists
    board.printPieceLists();
    cout << endl;

    int move_count = 0;
    const int max_moves = 1000; // set maximum limit
    while (true) {
        shared_ptr<ChessAI> current_ai = is_white ? ai1 : ai2; // black -> ai2 = onestep
        ChessMove move = current_ai->getMove(board, is_white);
        cout << "from " << move.from_x <<","<< move.from_y << " to " << move.to_x << "," << move.to_y << endl; 

        
        if (board.gameOver(is_white) || move == ChessMove(-1, -1, -1, -1, nullptr) || move_count >= max_moves){ // Game over or No legal moves left, or reached max_moves
            break;
        }
     
        board.movePiece(move);

        cout << endl;
        // Print the updated board
        cout << "Move by " << (is_white ? "White" : "Black") << ":" << endl;
        cout << board;
        // Print the updated piece lists
        board.printPieceLists();

        // Switch player
        is_white = !is_white;

        // Increment move count
        move_count++;
    }

    // Print the game result
    if (move_count >= max_moves) {
        cout << "Draw: Maximum number of moves reached." << endl;
    } else if (board.gameOver(is_white)) {
        cout << (is_white ? "White" : "Black") << " wins!" << endl;
    } 

    return 0;
}

