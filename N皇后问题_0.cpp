#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, cnt = 0;
vector<vector<string>> solutions;
vector<string> board;
vector<bool> cols;
vector<bool> diagonals;
vector<bool> anti_diagonals;

bool is_safe(int row, int col) {
    return !(cols[col] || diagonals[row - col + (n - 1)] || anti_diagonals[row + col]);
}

void place_queen(int row, int col) {
    board[row][col] = 'Q';
    cols[col] = true;
    diagonals[row - col + (n - 1)] = true;
    anti_diagonals[row + col] = true;
}

void remove_queen(int row, int col) {
    board[row][col] = '.';
    cols[col] = false;
    diagonals[row - col + (n - 1)] = false;
    anti_diagonals[row + col] = false;
}

void backtrack(int row) {
    if(row == n) {
        solutions.push_back(board);
        ++cnt;
        return;
    }

    for(int col = 0; col < n; col++) {
        if(is_safe(row, col)) {
            place_queen(row, col);
            backtrack(row + 1);
            remove_queen(row, col);
        }
    }
}

int main() {
    cin >> n;

    board.resize(n, string(n, '.'));
    cols.resize(n, false);
    diagonals.resize(2 * n - 1, false);
    anti_diagonals.resize(2 * n - 1, false);

    backtrack(0);

    for (const auto& solution : solutions) {
        for (const auto& row : solution) {
            cout << row << endl;
        }
        cout << endl; // 每个解之间添加空行以分隔
    }

    cout << "共有 " << cnt << " 种解决方案" << endl;

    return 0;
}