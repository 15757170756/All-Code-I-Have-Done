/*
https://leetcode.com/problems/combination-sum/

39. Combination Sum
Medium

1556

43

Favorite

Share
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
  [7],
  [2,2,3]
]
Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
Accepted
289,232
Submissions
632,166
Seen this question in a real interview before?
*/

class Solution {
public:

	void dfs(vector<int>& candidates, int sum,
		vector<vector<int>>& res, vector<int>& temp, int i)
	{
		if (sum < 0)
			return;
		if (sum == 0) {
			res.emplace_back(temp);
			return;
		}
		while (i < candidates.size() &&
			sum - candidates[i] >= 0) {
			temp.emplace_back(candidates[i]);
			dfs(candidates, sum - candidates[i], res, temp, i);
			++i;
			temp.pop_back();
		}
	}

	vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
	{
		sort(candidates.begin(), candidates.end());
		candidates.erase(unique(candidates.begin(), 
			candidates.end()),candidates.end());
		vector<vector<int>> res;
		vector<int> temp;
		dfs(candidates, target, res, temp, 0);
		return res;
	}
};

/*
Success
Details 
Runtime: 4 ms, faster than 100.00% of C++
 online submissions for Combination Sum.
*/


