class Solution:
    def relativeSortArray(self, arr1, arr2):
        arr1Len = len(arr1)
        arr2Len = len(arr2)
        res = [0 for i in range(arr1Len)]
        auxVec = [0 for i in range(1001)]
        for i in range(arr1Len):
            auxVec[arr1[i]] += 1

        j = 0
        for i in range(arr2Len):
            while auxVec[arr2[i]]:
                res[j] = arr2[i]
                j += 1
                auxVec[arr2[i]] -= 1

        for i in range(1001):
            while auxVec[i]:
                res[j] = i
                j += 1
                auxVec[i] -= 1

        return res

# Details 
# Runtime: 40 ms, faster than 50.00% of Python3 online submissions for Relative Sort Array.
# Memory Usage: 13.3 MB, less than 100.00% of Python3 online submissions for Relative Sort Array.


https://porn-4k.com
https://takefile.link
201203090212@zjut.edu.cn
7vLC5LwUEb6jPm7