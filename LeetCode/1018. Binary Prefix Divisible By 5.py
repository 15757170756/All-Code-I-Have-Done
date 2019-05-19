class Solution:
    def prefixesDivBy5(self, A):
        n = len(A)
        res = [False]*n
        arr = (1, 2, 4, 8, 6)
        sum = 0
        i = n - 1
        j = 0
        while i >= 0:
            idx = i % 4
            if i % 4 == 0:
                idx = 0
            elif idx == 0:
                idx = 4
            sum += arr[idx]*A[j]
            if sum % 5 == 0:
                res[j] = True
            else:
                res[j] = False
            i -= 1
            j += 1
        return res

# Success
# Details 
# Runtime: 104 ms, faster than 82.13% of Python3 online submissions for Binary Prefix Divisible By 5.
# Memory Usage: 16.1 MB, less than 100.00% of Python3 online submissions for Binary Prefix Divisible By 5.