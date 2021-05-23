#include <iostream>

class Move {
   public:
    int x1 = 1;  // in real chess, this is a char
    int y1 = 2;
    int x2 = 3;  // in real chess, this is a char
    int y2 = 4;
};

int* getPositionLegalMoves(int size) {
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = 1 + i;
    }

    return arr;
}

int main() {
    int* coolArray = getPositionLegalMoves(5);

    for (int i = 0; i < 5; i++) {
        std::cout << '|' << coolArray[i];
    }

    return 0;
}