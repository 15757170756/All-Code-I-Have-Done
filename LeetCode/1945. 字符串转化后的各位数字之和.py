class Solution:
    def getLucky(self, s, k):
        nums_lists = []
        for ch in s:
            nums_str = str(ord(ch) - ord('a') + 1)
            nums_lists.append(nums_str)
        nums_lists = ''.join(nums_lists)
        for idx in range(k):
            sum = 0
            for ch in nums_lists:
                sum += int(ch)
            nums_lists = str(sum)
        return sum

s = "leetcode"
k = 2
so = Solution()
print(so.getLucky(s, k))


# 提交结果：通过