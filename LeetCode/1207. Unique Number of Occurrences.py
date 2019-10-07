class Solution:
    def uniqueOccurrences(self, arr):
        n = len(arr)
        hashMap = [0 for i in range(2001)]
        for i in range(n):
            hashMap[arr[i] + 1000] += 1

        for i in range(2001):
            if 0 == hashMap[i]:
                continue
            for j in range(i + 1, 2001):
                if 0 == hashMap[j]:
                    continue
                if hashMap[i] == hashMap[j]:
                    return False

        return True


# Details 
# Runtime: 56 ms, faster than 10.52% of Python3 online submissions for Unique Number of Occurrences.
# Memory Usage: 13.8 MB, less than 100.00% of Python3 online submissions for Unique Number of Occurrences.