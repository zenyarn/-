#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long
using namespace std;

class BigInt {
private:
    string number;

public:
    // 构造函数，接受一个字符串来初始化
    BigInt(const string &num) : number(num) {
        auto it = number.find_first_not_of('0');
        number = (it == string::npos) ? "0" : number.substr(it);
    }

    // 从整型初始化
    BigInt(int num) : number(to_string(num)) {}

    // 加法运算
    BigInt operator+(const BigInt &other) const {
        string result;
        int carry = 0;
        int i = number.size() - 1, j = other.number.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? number[i--] - '0' : 0;
            int digit2 = (j >= 0) ? other.number[j--] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    // 乘法运算
    BigInt operator*(const BigInt &other) const {
        string result(number.size() + other.number.size(), '0');

        for (int i = number.size() - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = other.number.size() - 1; j >= 0; --j) {
                int product = (number[i] - '0') * (other.number[j] - '0') + (result[i + j + 1] - '0') + carry;
                carry = product / 10;
                result[i + j + 1] = (product % 10) + '0';
            }
            result[i] += carry;
        }

        auto it = result.find_first_not_of('0');
        result = (it == string::npos) ? "0" : result.substr(it);

        return BigInt(result);
    }

    // 输出运算
    friend ostream &operator<<(ostream &out, const BigInt &bigInt) {
        out << bigInt.number;
        return out;
    }
};

// 高精度版 count_sequences，返回值改为 BigInt 类型
BigInt count_sequences(int n, int m) {
    vector<vector<BigInt>> dp(n + 1, vector<BigInt>(m + 1, BigInt(0)));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = BigInt(1);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i >= j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return dp[n][m];
}

// 高精度版 factorial，返回值改为 BigInt 类型
BigInt factorial(int n) {
    BigInt result("1");
    for (int i = 2; i <= n; i++) {
        result = result * BigInt(i);
    }
    return result;
}

signed main() {
    int n, m;
    cin >> n >> m;

    BigInt result = factorial(n) * factorial(m) * count_sequences(n, m);
    cout << result << endl;

    return 0;
}