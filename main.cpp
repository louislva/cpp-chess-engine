#include <iostream>
#include <string>

// ♙♟ ♖ ♜ ♘ ♞ ♗ ♝ ♕ ♛ ♔ ♚

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

int main() {
    State state;

    state.render();
    std::cout << "Value: " << state.value() << std::endl;
    return 0;
}