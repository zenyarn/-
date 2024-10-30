c = 5
n = 100
m = 2

dp = [[0] * (c + 2) for _ in range(n + 1)]

dp[0][0] = 1
dp[1][1] = 1

for i in range(1, n):
    for j in range(c + 1):
        if dp[i][j] != 0:
            if j != 0:
                dp[i + 1][j - 1] += dp[i][j] * (j / c)
            dp[i + 1][j + 1] += dp[i][j] * (1 - (j / c))

for i in range(1, n + 1):
    for j in range(c + 1):
        if dp[i][j] != 0:
            print(f"dp[{i}][{j}] = {dp[i][j]}")
    print()

print(f"有{c}种巧克力, 取了{n}块, 此时剩余巧克力的概率情况如下: ")
for j in range(c + 1):
    if dp[n][j] != 0:
        print("有", j, "块的概率为", dp[n][j])