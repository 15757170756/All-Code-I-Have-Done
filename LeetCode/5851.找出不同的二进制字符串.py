class Solution:
    def findDifferentBinaryString(self, nums):
        n = len(nums)
        s = []
        for i in range(n):
            s.append(str(int(nums[i][i]) ^ 1))
        return ''.join(s)
