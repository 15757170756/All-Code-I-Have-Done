# https://leetcode-cn.com/problems/subsets/
# 78. 子集
# 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

# 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

 

# 示例 1：

# 输入：nums = [1,2,3]
# 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
# 示例 2：

# 输入：nums = [0]
# 输出：[[],[0]]
 

# 提示：

# 1 <= nums.length <= 10
# -10 <= nums[i] <= 10
# nums 中的所有元素 互不相同
# 通过次数224,550提交次数281,565

class Solution:
    def subsets(self, nums):
        res = [[]]
        for item in nums:
            new_subsets = [subset + [item] for subset in res]
            res = new_subsets + res
        return res


# 执行结果：
# 通过
# 显示详情
# 执行用时：
# 44 ms
# , 在所有 Python3 提交中击败了
# 35.55%
# 的用户
# 内存消耗：
# 15.1 MB
# , 在所有 Python3 提交中击败了
# 12.91%
# 的用户
# 炫耀一下: