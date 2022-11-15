#include <iostream>
#include <stack>
#include <vector>
#include <limits>

struct coordinate {
    int column;
    int row;

    coordinate(int x, int y) {
        column = x;
        row = y;
    }
};


int getn() {
    bool goahead = false;
    int n;
    while (goahead == false) {
        std::cout << "Please input the number of queens (Max: 20)." << std::endl << std::endl;
        std::cin >> n;
        std::cout << std::endl;
        if (!std::cin || n > 20) {
            std::cout << "That is not an input I can use. Try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            goahead = true;
        }
    }
    return n;
}

bool conflictCheck(std::vector<struct coordinate> queens, int curcolumn, int currow){
    if (queens.empty()) {
        return true;
    }
    for (int i = 0; i < queens.size(); i++) {
        coordinate check = queens[i];
        if (curcolumn == check.column) { //check if in the same column
            return false;
        }
        else if (((float)(currow - check.row) / (float)(curcolumn - check.column)) == 1) { //check if left diagonal
            return false;
        }
        else if (((float)(currow - check.row) / (float)(curcolumn - check.column)) == -1) { //check if right diagonal
            return false;
        }
    }
    return true;
}

void printBoard(std::vector<struct coordinate> queens, int n) {
    for (int i = queens.size() - 1; i >= 0; i--) {
        coordinate curQueen = queens[i];
        for (int j = 0; j <= n - 1; j++) {
            if (j == curQueen.column) {
                std::cout << "X ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

void NQueens(int n) {
    int filled = 0;
    std::vector<struct coordinate> queens;
    std::stack<int> stack;
    stack.push(0);
    while (filled < n) {
        bool safe = conflictCheck(queens, stack.top(), filled);
        int stackTop = stack.top();
        if (!safe && (stack.top() < n)) {
            int nextColumn = stack.top() + 1;
            stack.pop();
            stack.push(nextColumn);
        }
        else if ((stack.top() >= n)) {
            if (filled == 0) {
                std::cout << "No solution." << std::endl;
            }
            queens.pop_back();
            stack.pop();
            filled = filled--;
            int nextColumn = stack.top() + 1;
            stack.pop();
            stack.push(nextColumn);

        }
        else if (safe) {
            coordinate temp = coordinate(stack.top(), filled);
            queens.push_back(temp);
            filled = filled++;
            stack.push(0);
        }
    }
    for (int i = 0; i < n; i++) {
        coordinate temp = queens[i];
        std::cout << "[" << temp.column << "," << temp.row << "]";
    }
    std::cout << std::endl;
    printBoard(queens, n);
}

int main() {
    int n = getn();
    NQueens(n);
}