#include <iostream>
#include <vector>
//#define int long long
using namespace std;

int main() {
    int c, n, m;
    cin >> c >> n >> m;

    vector<vector<double>> dp(n + 1, vector<double>(c + 2, 0));

    dp[0][0] = 1;
    dp[1][1] = 1;

    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= c; j++) {
            if(dp[i][j] != 0) {
                if(j > 0) 
                    dp[i + 1][j - 1] += dp[i][j] * (double(j) / c);
                dp[i + 1][j + 1] += dp[i][j] * (1 - (double(j) / c));
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= c; j++) {
            cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
        }
        cout << endl;
    }

    cout << "有" << c << "种巧克力, 取了" << n << "块, 此时剩余巧克力的概率情况如下: " << endl;
    for(int j = 0; j <= c; j++) {
        if(dp[n][j] != 0) {
            cout << "有" << j << "块的概率为 " << dp[n][j] << endl;
        }
    }
    
    cout << endl;
    cout << "有" << m << "块的概率为 " << dp[n][m] << endl;

    return 0;
}
