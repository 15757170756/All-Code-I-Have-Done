<<<<<<< HEAD
"""
1980. 找出不同的二进制字符串
给你一个字符串数组 nums ，该数组由 n 个 互不相同 的二进制字符串组成，且每个字符串长度都是 n 。请你找出并返回一个长度为 n 且 没有出现 在 nums 中的二进制字符串。如果存在多种答案，只需返回 任意一个 即可。

 

示例 1：

输入：nums = ["01","10"]
输出："11"
解释："11" 没有出现在 nums 中。"00" 也是正确答案。
示例 2：

输入：nums = ["00","01"]
输出："11"
解释："11" 没有出现在 nums 中。"10" 也是正确答案。
示例 3：

输入：nums = ["111","011","001"]
输出："101"
解释："101" 没有出现在 nums 中。"000"、"010"、"100"、"110" 也是正确答案。
 

提示：

n == nums.length
1 <= n <= 16
nums[i].length == n
nums[i] 为 '0' 或 '1'
通过次数5,085提交次数8,842
请问您在哪类招聘中遇到此题？

"""

=======
>>>>>>> 16857503fa9abd38a3b1b14ebddf4a9f4670f371
class Solution:
    def findDifferentBinaryString(self, nums):
        n = len(nums)
        s = []
        for i in range(n):
            s.append(str(int(nums[i][i]) ^ 1))
        return ''.join(s)
