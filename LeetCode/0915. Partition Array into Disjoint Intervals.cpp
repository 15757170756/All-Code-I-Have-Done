/*
Given an array A, partition it into two (contiguous) subarrays left and right so that:

Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.

 

Example 1:

Input: [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
Example 2:

Input: [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]
 

Note:

2 <= A.length <= 30000
0 <= A[i] <= 10^6
It is guaranteed there is at least one way to partition A as described.
 
Seen this question in a real interview before?
*/

class Solution {
public:
	int partitionDisjoint(vector<int>& A) {
		int len = A.size();
		int idx = len - 2;
		vector<int> res;
		while (idx >= 0) {
			int max_num = A[0];
			for (int i = 0; i <= idx; ++i) {
				//Status: Time Limit Exceeded
				if (max_num < A[i])
					max_num = A[i];
			}
			int min_num = A[idx + 1];
			for (int i = idx+1; i < len; ++i) {
				if (min_num > A[i])
					min_num = A[i];
			}
			if (max_num <= min_num) {
				res.push_back(idx + 1);
				
			}
			--idx;
		}
		return *min_element(res.begin(), res.end());
	}
};
//Status: Time Limit Exceeded





class Solution {
public:
	int partitionDisjoint(vector<int>& A) {
		int len = A.size();
		int idx = len - 2;
		vector<int> res;
		while (idx >= 0) {
			int max_num = A[0];
			int max_idx = 0, min_idx = 0;
			for (int i = 0; i <= idx; ++i) {
				if (max_num <= A[i]) {
					max_num = A[i];
					max_idx = i;
				}
			}
			int min_num = A[idx + 1];
			for (int i = idx+1; i < len; ++i) {
				if (min_num >= A[i]) {
					min_num = A[i];
					min_idx = i;
				}
			}
			if (max_num <= min_num) {
				res.push_back(idx + 1);
				
			}
			idx = max_idx - 1;
		}
		return *min_element(res.begin(), res.end());
	}
};
//Runtime: 28 ms, faster than 97.53% of C++ online submissions 
//for Partition Array into Disjoint Intervals.