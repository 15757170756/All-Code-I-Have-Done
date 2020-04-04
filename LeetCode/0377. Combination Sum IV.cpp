/*
https://leetcode.com/problems/combination-sum-iv/

377. Combination Sum IV
Medium

1178

144

Add to List

Share
Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
 

Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

Credits:
Special thanks to @pbrother for adding this problem and creating all test cases.

Accepted
*/

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1);
        dp[0] = 1;
        sort (nums.begin(), nums.end());
        for (int i = 1; i <= target; i++) {
            for (auto num : nums) {
                if (i < num) break;
                dp[i] = ((long int)dp[i]+dp[i-num])%2147483647;
            }
        }
        return dp.back();
    }
};

/*
Success
Details 
Runtime: 0 ms, faster than 100.00% of C++ online submissions for Combination Sum IV.
Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Combination Sum IV.
Next challenges:
Distinct Subsequences
Push Dominoes
Maximum Students Taking Exam
Show off your acceptance:


*/