# import sys
# sys.stdin = open('input.txt', 'r')

class Solution:
    def maximumNumber(self, num, change):
        n = len(num)
        num = list(num)
        for i in range(n):
            if change[int(num[i])] > int(num[i]):
                while i < n and change[int(num[i])] >= int(num[i]):
                    num[i] = str(change[int(num[i])])
                    i += 1
                break
        return ''.join(num)


num = "132"
change = [9, 8, 5, 0, 3, 6, 4, 2, 6, 8]
so = Solution()
print(so.maximumNumber(num, change))

# 提交结果：通过
