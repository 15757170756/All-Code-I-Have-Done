/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		vector<vector<int>> res;
		int len = nums.size();
		sort(nums.begin(), nums.end());
		for (int i = 0; i < len; ++i) {
			int target = -nums[i];
			int front = i + 1;
			int back = len - 1;

			while (front < back) {
				int sum = nums[front] + nums[back];
				if (sum < target)
					++front;
				else if (sum > target)
					--back;
				else {
					vector<int> triplet(3, 0);
					triplet[0] = nums[i];
					triplet[1] = nums[front];
					triplet[2] = nums[back];
					res.push_back(triplet);
					while (front < back
						&& nums[front] == triplet[1])
						++front;
					while (front < back &&
						nums[back] == triplet[2])
						--back;
				}
			}
			while (i + 1 < len
				&& nums[i + 1] == nums[i])
				++i;
		}

		return res;
	}
};
