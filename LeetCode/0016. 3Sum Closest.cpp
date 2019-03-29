/*
Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int res = 0xfffff;
		int return_value;
		sort(nums.begin(), nums.end());
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			int aux_target = target - nums[i];
			int front = i + 1;
			int back = len - 1;
			while (front < back) {
				int sum = nums[front] + nums[back];

				int cur_min = abs(target -
					nums[i] - nums[front] - nums[back]);
				if (res > cur_min) {
					res = cur_min;
					return_value = nums[i] + nums[front]
						+ nums[back];
				}

				if (sum < aux_target) {
					++front;
				}
				else if (sum > aux_target)
					--back;
                else
					return return_value;
			}
		}
		return return_value;
	}
};