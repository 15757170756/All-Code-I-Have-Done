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
