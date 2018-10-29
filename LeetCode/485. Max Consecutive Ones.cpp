/*
485. Max Consecutive Ones
DescriptionHintsSubmissionsDiscussSolution
Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Seen this question in a real interview before?  

*/

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxLen = -1;
        int cnt = 0;
        for(int num:nums) {
            cnt = (num == 0 ? 0 : cnt + 1);
            maxLen = max(maxLen, cnt);
        }
        return maxLen;
    }
};

//Submission Result: Accepted 
