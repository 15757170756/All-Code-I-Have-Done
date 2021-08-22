class Helper:
    @staticmethod
    def next_permutation(nums):
        i = len(nums) - 2
        while i >= 0 and nums[i] >= nums[i + 1]:
            i -= 1
        if i < 0:
            return False
        if i >= 0:
            j = len(nums) - 1
            while j >= 0 and nums[i] >= nums[j]:
                j -= 1
            nums[i], nums[j] = nums[j], nums[i]
        left, right = i + 1, len(nums) - 1
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1
        return True


class Solution:
    def maxCompatibilitySum(self, students, mentors):
        m, n = len(students), len(students[0])
        g = [[0] * m for _ in range(m)]
        for i in range(m):
            for j in range(m):
                for k in range(n):
                    g[i][j] += int(students[i][k] == mentors[j][k])
        p = list(range(m))
        ans = 0
        while True:
            cur = sum(g[i][p[i]] for i in range(m))
            ans = max(ans, cur)
            if not Helper.next_permutation(p):
                break
        return ans


# 提交结果：通过




from itertools import permutations

class Solution:
    def maxCompatibilitySum(self, students, mentors):
        m, n = len(students), len(students[0])
        g = [[0] * m for _ in range(m)]
        for i in range(m):
            for j in range(m):
                for k in range(n):
                    g[i][j] += int(students[i][k] == mentors[j][k])

        permutations_list = list(permutations(range(m), m))
        ans = 0
        for idx, item in enumerate(permutations_list):
            cur = sum(g[i][item[i]] for i in range(m))
            ans = max(ans, cur)
        return ans

# 提交结果：通过