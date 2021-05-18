#include <iostream>
#include <string>

class State {
   public:
    int board[8][8] = {};
    State();
};
State::State(void) {
    std::cout << "Chess-board object is being created\n";
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
    return 0;
}