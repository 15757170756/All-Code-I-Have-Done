# https://leetcode-cn.com/problems/132-pattern/
# 456. 132 模式
# 给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。

# 如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false 。

 

# 进阶：很容易想到时间复杂度为 O(n^2) 的解决方案，你可以设计一个时间复杂度为 O(n logn) 或 O(n) 的解决方案吗？

 

# 示例 1：

# 输入：nums = [1,2,3,4]
# 输出：false
# 解释：序列中不存在 132 模式的子序列。
# 示例 2：

# 输入：nums = [3,1,4,2]
# 输出：true
# 解释：序列中有 1 个 132 模式的子序列： [1, 4, 2] 。
# 示例 3：

# 输入：nums = [-1,3,2,0]
# 输出：true
# 解释：序列中有 3 个 132 模式的的子序列：[-1, 3, 2]、[-1, 3, 0] 和 [-1, 2, 0] 。
 

# 提示：

# n == nums.length
# 1 <= n <= 104
# -109 <= nums[i] <= 109
# 通过次数41,293提交次数119,508
# 在真实的面试中遇到过这道题？


from sortedcontainers import SortedList

class Solution:
    def find132pattern(self, nums):
        n = len(nums)
        if n < 3:
            return False
        left_min = nums[0]
        right_all = SortedList(nums[2:])

        for j in range(1, n - 1):
            if left_min < nums[j]:
                index = right_all.bisect_right(left_min)
                if index < len(right_all) and right_all[index] < nums[j]:
                    return True
            left_min = min(left_min, nums[j])
            right_all.remove(nums[j+1])
        return False

# 显示详情
# 执行用时：
# 120 ms
# , 在所有 Python3 提交中击败了
# 27.84%
# 的用户
# 内存消耗：
# 16.2 MB
# , 在所有 Python3 提交中击败了
# 5.14%
# 的用户
# 炫耀一下:






class Solution:
    def find132pattern(self, nums):
        n = len(nums)
        candidate_k = [nums[n-1]]
        max_k = float('-inf')
        for i in range(n - 2, -1, -1):
            if nums[i] < max_k:
                return True
            while candidate_k and nums[i] > candidate_k[-1]:
                max_k = candidate_k[-1]
                candidate_k.pop()
            if nums[i] > max_k:
                candidate_k.append(nums[i])

        return False


# 显示详情
# 执行用时：
# 48 ms
# , 在所有 Python3 提交中击败了
# 91.24%
# 的用户
# 内存消耗：
# 15.6 MB
# , 在所有 Python3 提交中击败了
# 55.90%
# 的用户
# 炫耀一下: