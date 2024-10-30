#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

vector<int> get_max_matrix(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> pre_sum(rows, vector<int>(cols, 0));

    // 计算前缀和
    for (int j = 0; j < cols; j++) {
        int col_sum = 0;
        for (int i = 0; i < rows; i++) {
            col_sum += matrix[i][j];
            pre_sum[i][j] = col_sum;
        }
    }

    vector<int> a(cols, 0);
    int max_ans = numeric_limits<int>::min();
    vector<int> left_and_right(2, 0);
    vector<int> top_and_bottom(2, 0);

    // 求第i行到第j行的情况
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < rows; j++) {
            if (i == 0) {
                for (int k = 0; k < cols; k++) {
                    a[k] = pre_sum[j][k];
                }
            } else {
                for (int k = 0; k < cols; k++) {
                    a[k] = pre_sum[j][k] - pre_sum[i - 1][k];
                }
            }

            int dp_i = a[0];
            int begin = 0;
            if (dp_i > max_ans) {
                max_ans = dp_i;
                left_and_right[0] = begin;
                left_and_right[1] = begin;
                top_and_bottom[0] = i;
                top_and_bottom[1] = j;
            }

            for (int k = 1; k < cols; k++) {
                if (dp_i > 0) {
                    dp_i += a[k];
                } else {
                    dp_i = a[k];
                    begin = k;
                }

                if (dp_i > max_ans) {
                    max_ans = dp_i;
                    left_and_right[0] = begin;
                    left_and_right[1] = k;
                    top_and_bottom[0] = i;
                    top_and_bottom[1] = j;
                }
            }
        }
    }

    return {top_and_bottom[0], left_and_right[0], top_and_bottom[1], left_and_right[1], max_ans};
}

int main() {
    vector<vector<int>> matrix = {
        {0, -2, -7, 0},
        {9, 2, -6, 2},
        {-4, 1, -4, 1},
        {-1, 8, 0, -2}
    };

    vector<int> result = get_max_matrix(matrix);
    cout << "最大子矩阵的边界: (" << result[0] << ", " << result[1] << ") 到 (" << result[2] << ", " << result[3] << ")" << endl;

    cout << "最大子矩阵的和: " << result[4] << endl; // 输出最大子矩阵的和

    return 0;
}