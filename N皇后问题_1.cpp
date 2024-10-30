#include <iostream>
#include <vector>
#include <string>
#define int long long
using namespace std;

int n, cnt = 0;
vector<vector<string>> solutions;
vector<string> board;
int cols = 0; // 使用整数表示列的占用状态
int diagonals = 0; // 使用整数表示主对角线的占用状态
int anti_diagonals = 0; // 使用整数表示副对角线的占用状态

bool is_safe(int row, int col) {
    return !((cols >> col) & 1) && !((diagonals >> (row - col + (n - 1))) & 1) && !((anti_diagonals >> (row + col)) & 1);
}

void place_queen(int row, int col) {
    board[row][col] = 'Q';
    cols |= (1 << col); // 设置列的占用状态
    diagonals |= (1 << (row - col + (n - 1))); // 设置主对角线的占用状态
    anti_diagonals |= (1 << (row + col)); // 设置副对角线的占用状态
}

void remove_queen(int row, int col) {
    board[row][col] = '.';
    cols &= ~(1 << col); // 清除列的占用状态
    diagonals &= ~(1 << (row - col + (n - 1))); // 清除主对角线的占用状态
    anti_diagonals &= ~(1 << (row + col)); // 清除副对角线的占用状态
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

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;

    board.resize(n, string(n, '.'));

    backtrack(0);

    // for (const auto& solution : solutions) {
    //     for (const auto& row : solution) {
    //         cout << row << endl;
    //     }
    //     cout << endl; // 每个解之间添加空行以分隔
    // }

    cout << "共有 " << cnt << " 种解决方案" << endl;

    return 0;
}