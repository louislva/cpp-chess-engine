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
        {2, 3, 4, 5, 6, 4, 3, 2},         {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},         {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},         {0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1}, {-2, -3, -4, -5, -6, -4, -3, -2},
    };
    State();
    int value();
    void render();
    State stateTransitionFunction();
    std::vector<Move> getPositionMoves(int x, int y);
};
State::State(void) {}

int State::value() {
    int totalValue = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            // if it's a king, go nuts
            if (abs(this->board[y][x]) == 6) {
                totalValue += (this->board[y][x] * 10000);
            } else {
                totalValue += this->board[y][x];
            }
        }
    }
    return totalValue;
}

void State::render() {
    std::cout << "--------\n";
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            std::cout << renderChessPiece(this->board[y][x]);
        }
        std::cout << "\n";
    }
    std::cout << "--------\n";
}

std::vector<Move> State::getPositionMoves(int x, int y) {
    std::vector<Move> moves;

    int piece = this->board[y][x];
    bool black = piece < 0;
    int forwardMultiplier = black ? -1 : 1;

    switch (abs(piece)) {
        // EMPTY
        case 0: {
            return moves;
        }
        // PAWN
        case 1: {
            // moving forward by one or two
            moves.push_back(Move(x, y, x, y + (1 * forwardMultiplier)));
            moves.push_back(Move(x, y, x, y + (2 * forwardMultiplier)));

            // Left/right attacks
            moves.push_back(Move(x, y, x + 1, y + (1 * forwardMultiplier)));
            moves.push_back(Move(x, y, x - 1, y + (1 * forwardMultiplier)));
            return moves;
        }
        // ROOK
        case 2: {
            // Go through each direction (left, right, up, down), and add legal
            // moves until we hit another piece. If the piece we hit is from the
            // other color, we add that one, and THEN break. If it's our own, we
            // just break without adding it, because we cannot attack our own.
            // We determine whether the piece we hit is foreign, by multiplying
            // the "piece" and whatever piece we have. Two positives (whites) or
            // two negatives (blacks) makes positive value, and then we know
            // it's our own.

            for (int x2 = x + 1; x2 < 8; x2++) {
                if (piece * this->board[y][x2] > 0) break;
                moves.push_back(Move(x, y, x2, y));
                if (this->board[y][x2] != 0) break;
            }
            for (int y2 = y + 1; y2 < 8; y2++) {
                if (piece * this->board[y2][x] > 0) break;
                moves.push_back(Move(x, y, x, y2));
                if (this->board[y2][x] != 0) break;
            }
            for (int x2 = x - 1; x2 >= 0; x2--) {
                if (piece * this->board[y][x2] > 0) break;
                moves.push_back(Move(x, y, x2, y));
                if (this->board[y][x2] != 0) break;
            }
            for (int y2 = y - 1; y2 >= 0; y2--) {
                if (piece * this->board[y2][x] > 0) break;
                moves.push_back(Move(x, y, x, y2));
                if (this->board[y2][x] != 0) break;
            }
            return moves;
        }
        // HORSE
        case 3:
            return moves;
        // BISHOP
        case 4:
            return moves;
        // QUEEN
        case 5:
            return moves;
        // KING
        case 6:
            return moves;

        default:
            return moves;
            // TODO: throw
    }

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
    std::vector<Move> moves = state.getPositionMoves(0, 1);
    if (moves.size() > 0) {
        for (int i = 0; i < moves.size(); i++) {
            std::cout << moves.at(i).toString() << std::endl;
        }
    } else {
        std::cout << "Yoo man populate the moves" << std::endl;
    }

    return 0;
}