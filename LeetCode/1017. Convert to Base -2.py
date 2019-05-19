class Solution:
    def baseNeg2(self, N: int) -> str:
        res = ''
        while N:
            a = abs(N % (-2))
            res = ('0' if a == 0 else '1') + res
            N = (N - a) / (-2)

        return '0' if res == '' else res


# Success
# Details 
# Runtime: 36 ms, faster than 100.00% of Python3 online submissions for Convert to Base -2.
# Memory Usage: 13.4 MB, less than 100.00% of Python3 online submissions for Convert to Base -2.