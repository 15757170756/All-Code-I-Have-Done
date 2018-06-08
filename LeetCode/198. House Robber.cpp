/*
198. House Robber
DescriptionHintsSubmissionsDiscussSolution
You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed, 
the only constraint stopping you from robbing each of them 
is that adjacent houses have security system connected 
and it will automatically contact the police 
if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing
 the amount of money of each house, 
 determine the maximum amount of money 
 you can rob tonight without alerting the police.

Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) 
and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
Seen this question in a real interview before?  

*/

class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.size() == 0)
			return 0;
		if (nums.size() == 1)
			return nums[0];
		if (nums.size() == 2)
			return max(nums[0], nums[1]);
		if (nums.size() == 3)
			return max(nums[0] + nums[2], nums[1]);

		vector<int> max_money(nums.size());
		max_money[0] = nums[0];
		max_money[1] = nums[1];
		max_money[2] = max(nums[0] + nums[2], nums[1]);
		int result = max(max(max_money[0], max_money[1]), max_money[2]);
		for (int i = 3; i < nums.size(); i++)
		{
			max_money[i] = nums[i] + max(max_money[i - 2], max_money[i - 3]);
			result = max(result, max_money[i]);
		}
		return result;
	}
};
//Submission Result: Accepted 




class Solution {
public:
    int rob(vector<int>& nums) {
        int a = 0, b = 0;
        for(int num:nums) {
            int tmp = max(num+a, b);
            a = b;
            b = tmp;
        }
        return b;
    }
};

//Submission Result: Accepted 





f(0) = nums[0]
f(1) = max(num[0], num[1])
f(k) = max( f(k-2) + nums[k], f(k-1) )

class Solution:
    
    def rob(self, nums):
        
        last, now = 0, 0
        
        for i in nums: last, now = now, max(last + i, now)
                
        return now