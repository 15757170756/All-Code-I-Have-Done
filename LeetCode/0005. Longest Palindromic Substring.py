class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n <= 1:
            return s
        start = 0
        longest = 1
        dp = [[0 for i in range(n)] for j in range(n)]
        print(len(dp))

        for i in range(n):
            dp[i][i] = 1
            if i < n - 1 and s[i] == s[i+1]:
                dp[i][i+1] = 1
                start = i
                longest = 2
        for l in range(3, n+1):
            for i in range(n+1-l):
                j = l+i-1
                if s[i] == s[j] and \
                    dp[i+1][j-1] == 1:
                    dp[i][j] = 1
                    start = i
                    longest = l

        return s[start:start+longest]


# Runtime: 3680 ms, faster than 30.47% of Python3 online submissions for Longest Palindromic Substring.
# Memory Usage: 21.6 MB, less than 5.65% of Python3 online submissions for Longest Palindromic Substring.