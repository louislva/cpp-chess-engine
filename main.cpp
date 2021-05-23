#include <iostream>
#include <string>

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
};

State::State(void) { std::cout << "Chess-board object is being created\n"; }
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

int main() {
    State state;

    std::cout << "CHESS BOARD:\n";
    std::cout << "--------\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << state.board[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "--------\n";

    std::cout << "Value: " << state.value() << std::endl;
    return 0;
}