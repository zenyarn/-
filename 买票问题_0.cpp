#include <iostream>
#include <vector>
#define int long long
using namespace std;

int count_sequences(int n, int m) {
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(i >= j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return dp[n][m];
}

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

signed main() {
    int n, m;
    cin >> n >> m;

    cout << factorial(n) * factorial(m) * count_sequences(n, m) << endl;

    return 0;
}
