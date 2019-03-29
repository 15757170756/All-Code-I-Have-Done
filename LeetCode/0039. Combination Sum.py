class Solution:
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        answer = []
        stack = [([], 0, 0)]
        while stack:
            chosen, currSum, currIndex = stack.pop()
            if currSum == target:
                answer.append(chosen)
                continue
            if currSum > target:
                continue
            for i in range(currIndex, len(candidates)):
                candidate = candidates[i]
                stack.append((chosen + [candidate], currSum + candidate, i))
        return answer
# /*
# Success
# Details 
# Runtime: 112 ms, faster than 55.29% of Python3 
# online submissions for Combination Sum.
# */











class Solution:
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        answer = []
        stack = [([], 0, 0)]
        while stack:
            chosen, currSum, currIndex = stack.pop()
            if currSum == target:
                answer.append(chosen)
                continue
            if currSum > target:
                continue
            for i in range(currIndex, len(candidates)):
                candidate = candidates[i]
                if currSum + candidate <= target:
                    stack.append((chosen + [candidate], currSum + candidate, i))
        return answer      

# Success
# Details 
# Runtime: 64 ms, faster than 96.20% of Python3
#  online submissions for Combination Sum.
