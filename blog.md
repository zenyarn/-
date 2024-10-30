# 程序设计艺术与方法个人作业

> 从ICPC讲义中选择三个章节, 每个章节选择2个题目进行完成, 本题解多提供一个题, 共呈现如下七个题目:
> 选取的题目参考自: [ICPC讲义-2019.pdf][1]

- 实验二 搜索
    - 八皇后问题
    - N皇后问题
- 实验四 动态规划 
    - 计算给定矩阵的所有子矩阵中和的最大值 
    - 求两个字符串的最长公共子序列 
- 实验六 组合数学
    - 100个字符串的最长公共子序列 
    - 买票问题 
    - 巧克力问题

---

## 八皇后问题

**题目表述**

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
在一个4*4的国际象棋棋盘上放八个皇后，使得任何两个皇后之间不相互攻击，求出所有的布棋方法。

**思路解析**
见*N皇后问题*的思路解析

**参考代码**
见*N皇后问题*的参考代码

---

## N皇后问题

本题可参考该[LeetCode题目](https://leetcode.cn/problems/n-queens/description/)

**题目表述**

将八皇后问题推广到 N 皇后的情况，保证在 N 比较大的情况下，比方说 N=16 的时
候，你的程序能快速的求出结果.

**思路解析**

通过回溯法回溯遍历所有可能解.

**参考代码**

``` python
from typing import List

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        def is_safe(row, col):
            # 检查当前列和两条对角线是否有冲突
            return not (cols[col] or diagonals[row - col] or anti_diagonals[row + col])

        def place_queen(row, col):
            board[row][col] = 'Q'
            cols[col] = diagonals[row - col] = anti_diagonals[row + col] = True

        def remove_queen(row, col):
            board[row][col] = '.'
            cols[col] = diagonals[row - col] = anti_diagonals[row + col] = False

        def backtrack(row):
            if row == n:
                solutions.append(["".join(row) for row in board])
                return
            for col in range(n):
                if is_safe(row, col):
                    place_queen(row, col)
                    backtrack(row + 1)
                    remove_queen(row, col)

        # 初始化
        solutions = []
        board = [['.'] * n for _ in range(n)]
        cols = [False] * n
        diagonals = [False] * (2 * n - 1)
        anti_diagonals = [False] * (2 * n - 1)

        # 从第一行开始回溯
        backtrack(0)
        return solutions
```
本代码可提交LeetCode

---

## 计算给定矩阵的所有子矩阵中和的最大值

本题可参考该[LeetCode题](https://leetcode.cn/problems/max-submatrix-lcci/description/)

**题目表述**

输入一个矩阵，计算所有的子矩阵中和的最大值。 
例如，输入 
0 -2 -7 0 
9 2 -6 2 
-4 1 -4 1 
-1 8 0 -2 
输出为：15 
思考：当矩阵很大时，比如 100*100 的矩阵，你的程序还能够很快的得出结果吗.

**思路解析**

本思路参考自该[题解](https://leetcode.cn/problems/max-submatrix-lcci/solutions/137568/zhe-yao-cong-zui-da-zi-xu-he-shuo-qi-you-jian-dao-/)

首先我们尝试考虑求一个一维数组中连续一串元素的最大和(参考该[LeetCode题](https://leetcode.cn/problems/maximum-subarray/description/)), 可通过DP思路求解:
开一个`dp`数组, `dp[i]`表示加入`nums[i]`的情况下, 截止到第`i`元素的最大子对数组和,
当求解`dp[i]`时, 有两种可能的情况, 一种是和前面的子数组连起来, 另一种可能是从头开始, 
因此, 状态转移方程为: `dp[i] = max(dp[i-1] + nums[i], nums[i])`

最后, 遍历`dp`数组, 找到`dp`数组元素的最大值, 即为所求

``` python
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0

        if len(nums) == 1:
            return nums[0]

        dp = [0] * len(nums)
        dp[0] = nums[0]

        ret = dp[0]

        for i in range(len(nums)):
            dp[i] = max(dp[i-1] + nums[i], nums[i])
            ret = max(dp[i], ret)
        
        return ret
```

考虑到 dp[i-1] > 0 时, 一定会选取 dp[i] = dp[i-1] + nums[i] 的情况,
反之, 会选取 dp[i] = nums[i] 的情况, 故可进一步简化代码: 

``` python
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0

        if len(nums) == 1:
            return nums[0]

        dp_i = nums[0]

        ret = dp_i

        begin = 0
        ans = [0] * 2

        for i in range(1, len(nums)):
            if dp_i > 0:
                dp_i += nums[i]
            else:
                dp_i = nums[i]
                begin = i
            if dp_i > ret:
                ret = dp_i

                ans[0] = begin
                ans[1] = i
        
        return ret
```

故一维数组求最大子数组和的问题已经解决.
回到求最大子矩阵的问题, 只需要纵向求前缀和, 然后任取矩阵的第i行和第j行(i < j), 将前缀和相减即可得到从第i+1行到第j行的子矩阵的纵向元素和的一维数组, 并该一维数组上求解最大子数组和的问题, 即可求解i+1行开始, j行结束的情况下的最大子矩阵, 
遍历所有i, j的可能性, 记录所求得的最大值, 即可找到整个矩阵的最大子矩阵.

**参考代码**

``` python
class Solution:
    def getMaxMatrix(self, matrix: List[List[int]]) -> List[int]:
        rows, cols = len(matrix), len(matrix[0])
        pre_sum = [[0] * cols for _ in range(rows)]
        
        for j in range(cols):
            col_sum = 0
            for i in range(rows):
                col_sum += matrix[i][j]
                pre_sum[i][j] = col_sum
        
        a = [0] * cols
        max_ans = float('-inf')

        left_and_right = [0] * 2
        top_and_bottom = [0] * 2

        # 求第i行到第j行的情况
        for i in range(rows):
            for j in range(i, rows):
                if i == 0:
                    for k in range(cols):
                        a[k] = pre_sum[j][k]
                else:
                    for k in range(cols):
                        a[k] = pre_sum[j][k] - pre_sum[i - 1][k]

                dp_i = a[0]
                begin = 0
                if dp_i > max_ans:
                    max_ans = dp_i
                    left_and_right[0] = begin
                    left_and_right[1] = begin
                    top_and_bottom[0] = i
                    top_and_bottom[1] = j

                for k in range(1, cols):
                    if dp_i > 0:
                        dp_i += a[k]
                    else:
                        dp_i = a[k]
                        begin = k
                    

                    if dp_i > max_ans:
                        max_ans = dp_i
                        left_and_right[0] = begin
                        left_and_right[1] = k
                        top_and_bottom[0] = i
                        top_and_bottom[1] = j

        return [top_and_bottom[0], left_and_right[0], top_and_bottom[1], left_and_right[1]]
```
本代码可提交LeetCode

---

## 求两个字符串的最长公共子序列

本题可参考该[LeetCode题](https://leetcode.cn/problems/longest-common-subsequence/description/)

**题目表述**

给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列(LCS)。
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

**思路解析**

考虑用DP求解, 考虑到求解text1和text2的LCS与求解text2和text1的LCS是等价的, 故dp方程应有对称性.
准备二维dp数组`dp[i][j]`表示截止`text1[i-1]`和`text2[j-1]`所能找到的LCS的长度,
若`text1[i-1]`和`text2[j-1]`字符相同, `dp[i][j] = dp[i-1][j-1]+1`, 
若二者字符不同, 则text1或text2新追加的字符并不会使LCS增长, 则 `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`, 
如此便能求得LCS的长度, 最后, 通过回溯法反向寻找何时出现`text[i-1]`==`text[j-1]`的情况, 即可求得LCS

**参考代码**
``` python
def longest_common_subsequence(str1, str2):
    m, n = len(str1), len(str2)
    
    # 创建一个 (m+1) x (n+1) 的DP表，初始化为0
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # 填充DP表，计算最长公共子序列的长度
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    # 从表中回溯，构造最长公共子序列
    lcs = []
    i, j = m, n
    while i > 0 and j > 0:
        if str1[i - 1] == str2[j - 1]:
            lcs.append(str1[i - 1])  # 将公共字符加入lcs
            i -= 1
            j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1
    
    # 最终结果是逆序的，所以反转lcs
    lcs.reverse()
    
    return dp[m][n], ''.join(lcs)

# 测试
str1 = "abcde"
str2 = "ace"
length, lcs_string = longest_common_subsequence(str1, str2)
print("长度:", length)  # 输出: 3
print("最长公共子序列:", lcs_string)  # 输出: "ace"
```

---

## 100个字符串的最长公共子序列

**题目表述**

参考上一题中最长公共子序列的概念, 考虑一下怎么求100个字符串的最长公共子序列.

**思路解析**

基于上一题求解LCS的方法, 取前两个字符串的LCS的结果, 然后依次和后面的字符串取LCS即可.

**参考代码**
``` python
import random
import string

# 生成随机字符串
def generate_random_string(length):
    char_set = string.digits + string.ascii_letters
    rand_str = ''.join(random.choice(char_set) for _ in range(length))
    return rand_str

# 求两个字符串的最长公共子序列
def longest_common_subsequence(text1: str, text2: str) -> str:
    len1, len2 = len(text1), len(text2)
    
    # 初始化 (len1+1) x (len2+1) 的DP表
    dp = [[0] * (len2 + 1) for _ in range(len1 + 1)]

    # 填充DP表
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if text1[i - 1] == text2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    
    # 回溯出LCS
    i, j = len1, len2
    lcs = []

    while i > 0 and j > 0:
        if text1[i - 1] == text2[j - 1]:
            lcs.append(text1[i - 1])
            i -= 1
            j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1

    lcs.reverse()

    return ''.join(lcs)

# 标注LCS中的字符
def highlight_lcs_in_string(string, lcs):
    highlighted = []
    lcs_idx = 0

    for char in string:
        if lcs_idx < len(lcs) and char == lcs[lcs_idx]:
            highlighted.append(f"  [{char}]  ")  # 使用方括号标注LCS字符
            lcs_idx += 1
        else:
            highlighted.append(char)

    return ''.join(highlighted)

def test():
    # 生成500个长度为500的随机字符串
    random_strings = [generate_random_string(1000) for _ in range(500)]

    # 从第一个字符串开始，逐步求解LCS
    common_lcs = random_strings[0]
    for i in range(1, len(random_strings)):
        common_lcs = longest_common_subsequence(common_lcs, random_strings[i])
        if not common_lcs:
            break  # 如果LCS为空，提前结束

    print("最长公共子序列:", common_lcs)

    # 打印每个字符串并标注LCS中的字符
    print("\n标注后的字符串:")
    for i, rand_str in enumerate(random_strings):
        highlighted_str = highlight_lcs_in_string(rand_str, common_lcs)
        print(f"字符串 {i + 1}: {highlighted_str}")

test()
```

---

## 买票问题

**题目表述**

电影院卖电影票，但是没有零钱找，票价一张 5 元，买票的人为 n 个持有 5 元，m 个持
有 10 元，求解出可能的买票序列的个数，使得电影院能够将票卖完。例如，n=3,m=3
时 ， 输 出  180 。   当 n=5,m=3 时 ， 输 出  20160 。  当 n=100,m=100 时 ， 输 出 
780849373628505449061745756368500061678352453155617092371032211133029158379
607270218123053477212498915026942711801622604215487911131323866397947153418
643496151943423040359720037026721726655886753912538851736666625608050720226
034508195568556839182082416159660797603533326956467231851806002328416691877
4048734879105185187102720000000000000000000000000000000000000000000000000。

**思路解析**

采用动态规划, `dp[i][j]` 表示有 i 个 5 元顾客和 j 个 10 元顾客时，符合条件的序列数。
考虑到需要找零钱, 当且仅当 i>=j 时, `dp[i][j]`是有效的(无效的dp状态被默认初始化为0), 此时的转移方程为: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`, 
特别地, 当 i=j 时, `dp[i-1][j]`是无效的, 此时 `dp[i][j] = dp[i][j-1]`

**参考代码**

``` python
def count_sequences(n: int, m: int) -> int:
    # 初始化 DP 数组，dp[i][j] 表示 i 个 5 元和 j 个 10 元时的排列数
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    
    # 初始条件：如果没有 10 元的人，任何排列都是合法的
    for i in range(n + 1):
        dp[i][0] = 1
    
    # 填充 DP 表
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if i >= j:  # 确保 5 元的人数不少于 10 元的人数
                dp[i][j] = dp[i-1][j] + dp[i][j-1]
    
    return dp[n][m]

def factorial(n: int) -> int:
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

def main():
    n = int(input())
    m = int(input())

    print(factorial(n) * factorial(m) * count_sequences(n, m))  # 输出应该为 5

main()
```

---

## 巧克力问题

**题目表述**

有袋子里均匀地装着 c 种颜色的巧克力，每种巧克力均有无限多。每次从袋子里拿一块
放在桌子上，如果桌子上已经有一块颜色相同的巧克力，就把两块巧克力都吃掉。一共
取出了 n 块巧克力，问：最后桌子上有 m 块的概率为多大。例如 c=5,n=100,m=2 时，概
率为 0.625。

**思路解析**

采用动态规划求解, `dp[i][j]`表示取了i次巧克力, 此时桌子上剩余j块巧克力的概率.
考虑一下, 当取第i+1块巧克力时, 可能出现如下两种情况:
① 第i+1块巧克力与剩余的某块巧克力同色, 被一同吃掉, 巧克力数-1, 状态转移至 `dp[i+1][j-1]`, 该情况发生的概率为 `dp[i][j]*(j/c)`
② 第i+1块巧克力与剩余的巧克力颜色都不同, 巧克力数+1, 状态转移至 `dp[i+1][j+1]`, 该情况发生的概率为 `dp[i][j]*(1-(j/c))`
注意, `dp[i][j-1]`和`dp[i][j+1]`都可以状态转移至`dp[i+1][j]`, 故`dp`数组的值应该是累加的, 赋值时要用 `+=` , 而非 `=`.

**参考代码**

``` python
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
```

  [1]: http://zhenyutongxue.com/usr/uploads/2024/10/817760826.pdf