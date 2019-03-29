/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:

Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 
Note:

There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?

Seen this question in a real interview before?
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        if(len == 0)
            return 0;
        vector<int> auxVec(len, 1);
        for(int i = 1; i < len; ++i) {
            for(int j = 0; j < i; ++j) {
                if(nums[i] > nums[j])
                    auxVec[i] = max(auxVec[i], auxVec[j] + 1);
            }
        }
        return *max_element(auxVec.begin(), auxVec.end());
    }
};


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0)
		    return nums.size();

        vector<int>::iterator m = nums.begin();  // m will mark the virtual "S.end()".
        for (int& val : nums) {
            auto it = lower_bound(nums.begin(), m, val);
            *it = val;
            if (it == m)
                m++;
        }

        return m - nums.begin();
    }
};