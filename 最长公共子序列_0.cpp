#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long
using namespace std;

string longest_common_subsequence(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string lcs;
    int i = m, j = n;
    while(i > 0 && j > 0) {
        if(str1[i - 1] == str2[j - 1]) {
            lcs += str1[i - 1];
            i--;
            j--;
        } else if(dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

signed main() {
    string str1, str2;
    cin >> str1 >> str2;

    string lcs = longest_common_subsequence(str1, str2);
    cout << lcs << endl;

    return 0;
}
