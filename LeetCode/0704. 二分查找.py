<<<<<<< HEAD
"""
704. 二分查找
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。


示例 1:

输入: nums = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 出现在 nums 中并且下标为 4
示例 2:

输入: nums = [-1,0,3,5,9,12], target = 2
输出: -1
解释: 2 不存在 nums 中因此返回 -1
 

提示：

你可以假设 nums 中的所有元素是不重复的。
n 将在 [1, 10000]之间。
nums 的每个元素都将在 [-9999, 9999]之间。
通过次数209,575提交次数377,652
"""

=======
>>>>>>> 16857503fa9abd38a3b1b14ebddf4a9f4670f371
class Solution:
    def search(self, nums, target):
        n = len(nums)
        left, right = 0, n - 1
        mid = (left + right) // 2
        while left <= right:
            if target > nums[mid]:
                left = mid + 1
            elif target < nums[mid]:
                right = mid - 1
            else:
                return mid
            mid = (left + right) // 2
        return -1

# 执行结果：
# 通过
# 显示详情
# 添加备注

# 执行用时：
# 36 ms
# , 在所有 Python3 提交中击败了
# 85.84%
# 的用户
# 内存消耗：
# 15.8 MB
# , 在所有 Python3 提交中击败了
# 47.84%
# 的用户
