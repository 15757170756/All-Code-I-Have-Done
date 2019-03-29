/*
Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
Seen this question in a real interview before?
*/

class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			int other_target1 = target - nums[i];
			for (int j = i + 1; j < len; ++j) {
				int other_target2 = other_target1 - nums[j];
				int front = j + 1;
				int back = len - 1;
				while (front < back) {
					int sum = nums[front] + nums[back];
					if (sum < other_target2)
						++front;
					else if (sum > other_target2)
						--back;
					else {
						vector<int> quadra(4, 0);
						quadra[0] = nums[i];
						quadra[1] = nums[j];
						quadra[2] = nums[front];
						quadra[3] = nums[back];
						res.push_back(quadra);
						while (front < back &&
							nums[front] == quadra[2])
							++front;
						while (front < back &&
							nums[back] == quadra[3])
							--back;

					}
				}
				while (j + 1 < len &&
					nums[j] == nums[j + 1])
					++j;
			}
			while (i + 1 < len
				&& nums[i + 1] == nums[i])
				++i;
		}
		return res;
	}
};