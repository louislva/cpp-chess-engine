#include <iostream>
#include <string>
#include <vector>

const char X_AXIS_LABELS[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

std::string renderChessPiece(int n) {
    bool black = n < 0;

    switch (abs(n)) {
        case 0:
            return " ";
        case 1:
            return black ? "♙" : "♟";
        case 2:
            return black ? "♖" : "♜";
        case 3:
            return black ? "♘" : "♞";
        case 4:
            return black ? "♗" : "♝";
        case 5:
            return black ? "♕" : "♛";
        case 6:
            return black ? "♔" : "♚";

        default:
            break;
    }
}

class Move {
   public:
    int x1 = 1;  // in real chess, this is a char
    int y1 = 2;
    int x2 = 3;  // in real chess, this is a char
    int y2 = 4;
    Move(int x1, int y1, int x2, int y2);
    Move(char x1, int y1, char x2, int y2);
    std::string toString();
};
// Machine constructor (every position is int from 0-7)
Move::Move(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}
// Human constructor (x is A-H; y is 1-8)
Move::Move(char x1, int y1, char x2, int y2) {
    this->x1 = std::find(X_AXIS_LABELS, X_AXIS_LABELS + 8, x1) - X_AXIS_LABELS;
    this->y1 = y1 - 1;
    this->x2 = std::find(X_AXIS_LABELS, X_AXIS_LABELS + 8, x2) - X_AXIS_LABELS;
    this->y2 = y2 - 1;
}

std::string Move::toString() {
    return X_AXIS_LABELS[this->x1] + std::to_string(this->y1 + 1) + "->" +
           X_AXIS_LABELS[this->x2] + std::to_string(this->y2 + 1);
}
class State {
   public:
    int board[8][8] = {
        {-2, -3, -4, -5, -6, -4, -3, -2}, {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, 0, 0, 0, 0, 0},         {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},         {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},         {2, 3, 4, 5, 6, 4, 3, 2},
    };
    State();
    int value();
    void render();
    State stateTransitionFunction();
    std::vector<Move> getPositionLegalMoves();
};
State::State(void) {}

int State::value() {
    int totalValue = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // if it's a king, go nuts
            if (abs(this->board[i][j]) == 6) {
                totalValue += (this->board[i][j] * 10000);
            } else {
                totalValue += this->board[i][j];
            }
        }
    }
    return totalValue;
}

void State::render() {
    std::cout << "--------\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << renderChessPiece(this->board[i][j]);
        }
        std::cout << "\n";
    }
    std::cout << "--------\n";
}

std::vector<Move> State::getPositionLegalMoves() {
    std::vector<Move> moves;
    moves.push_back(Move('A', 2, 'A', 4));

    return moves;

    // what is my piece?
    // under the best circumstances, which moves are avaible?
    // filter to match actual circumstances
}

// getLegalMoves(bool black){ return Move[?]; }
State State::stateTransitionFunction(/* move */) {
    State newState;

    // Take move
    // Validate move
    // If valid, return new board, with potentially taken pieces removed

    return newState;
}

int main() {
    State state;

    state.render();
    std::cout << "Value: " << state.value() << std::endl;

    std::cout << state.getPositionLegalMoves()[0].toString() << std::endl;

    return 0;
}