# https://leetcode-cn.com/problems/subsets-ii/
# 90. 子集 II
# 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

# 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

 

# 示例 1：

# 输入：nums = [1,2,2]
# 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
# 示例 2：

# 输入：nums = [0]
# 输出：[[],[0]]
 

# 提示：

# 1 <= nums.length <= 10
# -10 <= nums[i] <= 10
# 通过次数94,570提交次数149,958

class Solution:
    def subsetsWithDup(self, nums):
        res = [[]]
        nums.sort()
        for i, item in enumerate(nums):
            if i >= 1 and nums[i] == nums[i-1]:
                new_subsets = [subset + [item] for subset in new_subsets]
            else:
                new_subsets = [subset + [item] for subset in res]
            res = new_subsets + res
        return res


# 执行结果：
# 通过
# 显示详情
# 执行用时：
# 32 ms
# , 在所有 Python3 提交中击败了
# 96.95%
# 的用户
# 内存消耗：
# 15.1 MB
# , 在所有 Python3 提交中击败了
# 17.02%
# 的用户
# 炫耀一下: