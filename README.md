# Custom Chess Game with AI

This chess game is implemented in C++ and features two distinct AI opponents: **Random AI** and **One Step Ahead AI**. Unlike traditional chess programs, this game does not use a matrix representation for the board; instead, it tracks all game information through the list of chess pieces.

**The player who loses all of their pieces first wins! When a player can capture a piece of the opponent, they must do so.**

## AI Strategies

- **Random AI:** Makes moves at random, including random choices for pawn promotion.
- **One Step Ahead AI:** Strategically aims to force the opponent into making captures. It evaluates the immediate consequences of moves and prefers pawn promotions that do not immediately lead to the capturing of the opponent's pieces. It tries to compel the opponent to capture, looking slightly ahead to anticipate the game's potential outcomes.


![Two onestep AIs playing](img/chess.gif)


### Compilation

* Compile the game with the following command:

```bash
g++ -std=c++17 -o chess main.cpp Bishop.cpp ChessAI.cpp ChessBoard.cpp ChessMove.cpp ChessPiece.cpp King.cpp Knight.cpp OneStepAheadAI.cpp Pawn.cpp Queen.cpp RandomAI.cpp Rook.cpp
```

* run: 
```bash
./chess [starting_color] [ai_type for white] [ai_type for black] [input_filename]
```

- `starting_color`: Either `white` or `black`.
- `ai_type`: Choose between `random` or `onestep` for both white and black players.
- `input_filename`: Path to a file containing the initial board configuration (e.g., `board.in`).

## Testing

* compile tests: 
```bash
g++ -std=c++17 -o chess tests.cpp Bishop.cpp ChessAI.cpp ChessBoard.cpp ChessMove.cpp ChessPiece.cpp King.cpp Knight.cpp OneStepAheadAI.cpp Pawn.cpp Queen.cpp RandomAI.cpp Rook.cpp
```

* run tests: 
```bash
./chess < tests.in
```

