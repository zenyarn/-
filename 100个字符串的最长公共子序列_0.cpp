#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// 生成随机字符串
string generate_random_string(int length) {
    const string char_set = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string rand_str;
    random_device rd;  // 获取随机数种子
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, char_set.size() - 1);

    for (int i = 0; i < length; ++i) {
        rand_str += char_set[distribution(generator)];
    }
    return rand_str;
}

// 求两个字符串的最长公共子序列
string longest_common_subsequence(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs += str1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// 标注LCS中的字符
string highlight_lcs_in_string(const string& str, const string& lcs) {
    string highlighted;
    size_t lcs_idx = 0;

    for (char char_str : str) {
        if (lcs_idx < lcs.size() && char_str == lcs[lcs_idx]) {
            highlighted += " [" + string(1, char_str) + "] ";  // 使用方括号标注LCS字符
            lcs_idx++;
        } else {
            highlighted += char_str;
        }
    }

    return highlighted;
}

int main() {
    const int num_strings = 100;
    const int string_length = 1000;

    // 生成100个长度为1000的随机字符串
    vector<string> random_strings(num_strings);
    for (int i = 0; i < num_strings; ++i) {
        random_strings[i] = generate_random_string(string_length);
    }

    // 从第一个字符串开始，逐步求解LCS
    string common_lcs = random_strings[0];
    for (int i = 1; i < random_strings.size(); ++i) {
        common_lcs = longest_common_subsequence(common_lcs, random_strings[i]);
        if (common_lcs.empty()) {
            break;  // 如果LCS为空，提前结束
        }
    }

    cout << "最长公共子序列: " << common_lcs << endl;

    // 打印每个字符串并标注LCS中的字符
    cout << "\n标注后的字符串:" << endl;
    for (int i = 0; i < random_strings.size(); ++i) {
        string highlighted_str = highlight_lcs_in_string(random_strings[i], common_lcs);
        cout << "字符串 " << (i + 1) << ": " << highlighted_str << endl;
    }

    cout << "最长公共子序列: " << common_lcs << endl;

    return 0;
}