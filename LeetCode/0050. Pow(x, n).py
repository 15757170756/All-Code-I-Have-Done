# https://leetcode-cn.com/problems/powx-n/
# 50. Pow(x, n)
# 实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。

 

# 示例 1：

# 输入：x = 2.00000, n = 10
# 输出：1024.00000
# 示例 2：

# 输入：x = 2.10000, n = 3
# 输出：9.26100
# 示例 3：

# 输入：x = 2.00000, n = -2
# 输出：0.25000
# 解释：2-2 = 1/22 = 1/4 = 0.25
 

# 提示：

# -100.0 < x < 100.0
# -231 <= n <= 231-1
# -104 <= xn <= 104
# 通过次数169,935提交次数454,447


class Solution:
    def myPow(self, x: float, n: int) -> float:
        if n < 0:
            return 1/self.myPow(x, -n)
        number = 1
        while n:
            if n & 1:
                number = number * x
            n >>= 1
            x = x * x
        return number


# Pow(x, n)
# 提交记录
# 304 / 304 个通过测试用例
# 状态：通过
# 执行用时: 44 ms
# 内存消耗: 14.8 MB
