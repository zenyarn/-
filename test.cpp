#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long
using namespace std;

string longest_common_substring(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int max_length = 0;
    int end_index = 0;

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                if(dp[i][j] > max_length) {
                    max_length = dp[i][j];
                    end_index = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    string ret = str1.substr(end_index - max_length, end_index);
    return ret;
}

signed main() {
    string str1, str2;
    cin >> str1 >> str2;

    string ans = longest_common_substring(str1, str2);
    cout << ans << endl;

    return 0;
}
