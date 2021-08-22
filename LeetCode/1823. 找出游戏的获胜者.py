class Solution:
    def findTheWinner(self, n, k):
        p = 0
        for i in range(2, n + 1):
            p = (p + k) % i
        return p + 1
# 执行用时：
# 40 ms
# , 在所有 Python3 提交中击败了
# 82.28%
# 的用户
# 内存消耗：
# 14.5 MB
# , 在所有 Python3 提交中击败了
# 99.65%
# 的用户

from queue import Queue
class Solution:
    def findTheWinner(self, n, k):
        q_cir = Queue(maxsize=500)
        for i in range(1, n+1):
            q_cir.put(i)
        for i in range(1, n):
            for j in range(1, k):
                q_cir.put(q_cir.get())
            q_cir.get()
        return q_cir.get()


# 执行用时：
# 9548 ms
# , 在所有 Python3 提交中击败了
# 5.01%
# 的用户
# 内存消耗：
# 14.9 MB
# , 在所有 Python3 提交中击败了
# 60.25%
# 的用户
# 炫耀一下: