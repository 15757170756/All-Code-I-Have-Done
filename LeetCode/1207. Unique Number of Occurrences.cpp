/*
https://leetcode.com/problems/unique-number-of-occurrences/

1207. Unique Number of Occurrences
Easy

36

2

Favorite

Share
Given an array of integers arr, write a function that returns true if and only if the number of occurrences of each value in the array is unique.

 

Example 1:

Input: arr = [1,2,2,1,1,3]
Output: true
Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
Example 2:

Input: arr = [1,2]
Output: false
Example 3:

Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
Output: true
 

Constraints:

1 <= arr.length <= 1000
-1000 <= arr[i] <= 1000
Accepted
8.1K
Submissions
10.6K
Seen this question in a real interview before?
*/

class Solution {
public:
	bool uniqueOccurrences(vector<int>& arr) {
		vector<int> hashMap(2001, 0);
		for (int i = 0; i < arr.size(); ++i) {
			hashMap[arr[i] + 1000]++;
		}
		//sort(hashMap.begin(), hashMap.end());
		for (int i = 0; i < hashMap.size(); ++i) {
			if(0 == hashMap[i])
				continue;
			for (int j = i + 1; j < hashMap.size(); ++j) {
				if(0 == hashMap[j])
					continue;
				if (hashMap[i] == hashMap[j])
					return false;
			}
		}
		return true;
	}
};

/*
Details 
Runtime: 0 ms, faster than 100.00% of C++ online submissions for Unique Number of Occurrences.
Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Unique Number of Occurrences.
*/



class Solution {
public:
	bool uniqueOccurrences(vector<int>& arr) {
		vector<int> hashMap(2001, 0);
		for (int i = 0; i < arr.size(); ++i) {
			hashMap[arr[i] + 1000]++;
		}
		sort(hashMap.begin(), hashMap.end());
		for (int i = 0; i < hashMap.size() - 1; ++i) {
			if(0 == hashMap[i])
				continue;
			if (hashMap[i] == hashMap[i + 1])
				return false;
		}
		return true;
	}
};

/*
Success
Details 
Runtime: 12 ms, faster than 11.68% of C++ online submissions for Unique Number of Occurrences.
Memory Usage: 9.4 MB, less than 100.00% of C++ online submissions for Unique Number of Occurrences.
*/
