/*
1. Two Sum
DescriptionHintsSubmissionsDiscussSolution
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
		int lens = nums.size();
		vector<int> result;
		for (int i = 0; i < lens; ++i) {
			for (int j = lens - 1; j > i;) {
				if (target == nums[i] + nums[j]) {
					result.push_back(i);
					result.push_back(j);
					return result;
				}
				else
					--j;
			}
		}
		return result;
	}
};




class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target)
	{
		//Key is the number and value is its index in the vector.
		unordered_map<int, int> hash;
		vector<int> result;
		for (int i = 0; i < numbers.size(); i++) {
			int numberToFind = target - numbers[i];

			//if numberToFind is found in map, return them
			if (hash.find(numberToFind) != hash.end()) {
				//+1 because indices are NOT zero based
				result.push_back(hash[numberToFind] + 1);
				result.push_back(i + 1);			
				return result;
			}

			//number was not found. Put it in the map.
			hash[numbers[i]] = i;
		}
		return result;
	}	
}