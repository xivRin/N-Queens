#include <iostream>
#include <stack>
#include <vector>
#include <limits>

// struct for coordinates
struct coordinate {
    int column;
    int row;

    coordinate(int x, int y) {
        column = x;
        row = y;
    }
};

// gets input for n in NQueens
int getn() {
    bool goahead = false;
    int n;
    while (goahead == false) {
        std::cout << "Please input the number of queens (Max: 20)." << std::endl << std::endl;
        std::cin >> n;
        std::cout << std::endl;
        if (!std::cin || n > 20) { //checks to see if input fits int n and is less than 20, if not, repeat.
            std::cout << "That is not an input I can use. Try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            goahead = true; // if criteria are met, return n and break loop
        }
    }
    return n;
}

//checks for conflict issues with queens
bool conflictCheck(std::vector<struct coordinate> queens, int curcolumn, int currow){
    if (queens.empty()) { //if queens vector is empty, there is no conflict.
        return true;
    }
    for (int i = 0; i < queens.size(); i++) {
        coordinate check = queens[i];
        if (curcolumn == check.column) { //check if queen is in the same column.
            return false;
        }
        else if (((float)(currow - check.row) / (float)(curcolumn - check.column)) == 1) { //check if left diagonal is a conflict.
            return false;
        }
        else if (((float)(currow - check.row) / (float)(curcolumn - check.column)) == -1) { //check if right diagonal is a conflict.
            return false;
        }
    }
    return true;
}

//prints board
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

//main NQueens function. Prints queen positions and board.
void NQueens(int n) {
    int filled = 0; //initialization
    std::vector<struct coordinate> queens;
    std::stack<int> stack;
    stack.push(0);
    while (filled < n) { //run until filled = n
        bool safe = conflictCheck(queens, stack.top(), filled);
        int stackTop = stack.top();
        if (!safe && (stack.top() < n)) { //run if conflict and there are remaining columns.
            int nextColumn = stack.top() + 1; //pop column and move one over.
            stack.pop();
            stack.push(nextColumn);
        }
        else if ((stack.top() >= n)) { //run if there are no remaining columns to move.
            if (filled == 0) { //return no solution
                std::cout << "No solution." << std::endl;
            }
            queens.pop_back(); //pop stack and vector because queen is invalid.
            stack.pop();
            filled = filled - 1; //reduce filled by 1.
            int nextColumn = stack.top() + 1; //go to previous row and move one column.
            stack.pop();
            stack.push(nextColumn);
        }
        else if (safe) { //no conflict.
            coordinate temp = coordinate(stack.top(), filled); //push queen position to vector and push to stack.
            queens.push_back(temp);
            filled = filled + 1; //increment filled by 1
            stack.push(0); //push fresh row.
        }
    }
    std::cout << "Queen Positions:" << std::endl;
    for (int i = 0; i < n; i++) { //prints queen positions (x + 1, y + 1) for readability. 
        coordinate temp = queens[i];
        std::cout << "[" << temp.column + 1 << "," << temp.row + 1 << "]";
    }
    std::cout << std::endl; 
    if (!queens.empty()) { //if vector is not empty (due to no solution), print the board.
    	printBoard(queens, n);
    }
}

int main() { //main function. Get n, run nQueens.
    int n = getn();
    NQueens(n);
}
