/*
https://leetcode.com/problems/binary-prefix-divisible-by-5/
1018. Binary Prefix Divisible By 5
Easy

19

19

Favorite

Share
Given an array A of 0s and 1s, consider N_i: the i-th subarray from A[0] to A[i] interpreted as a binary number (from most-significant-bit to least-significant-bit.)

Return a list of booleans answer, where answer[i] is true if and only if N_i is divisible by 5.

Example 1:

Input: [0,1,1]
Output: [true,false,false]
Explanation: 
The input numbers in binary are 0, 01, 011; which are 0, 1, and 3 in base-10.  Only the first number is divisible by 5, so answer[0] is true.
Example 2:

Input: [1,1,1]
Output: [false,false,false]
Example 3:

Input: [0,1,1,1,1,1]
Output: [true,false,false,false,true,false]
Example 4:

Input: [1,1,1,0,1]
Output: [false,false,false,false,false]
 

Note:

1 <= A.length <= 30000
A[i] is 0 or 1
Accepted
4,909
Submissions
11,295
*/

class Solution {
public:
	vector<bool> prefixesDivBy5(vector<int>& A) {
		int len = A.size();
		vector<bool> res(len);
		int arr[] = { 1,2,4,8,6 };
		int sum = 0;
		for (int i = len - 1, j = 0;
			i >= 0; --i, ++j) {
			int idx = i % 4;
			if (i == 0)
				idx = 0;
			else if (idx == 0)
				idx = 4;
			sum += arr[idx]*A[j];
			if (sum % 5 == 0)
				res[j] = true;
			else
				res[j] = false;
		}
		return res;
	}
};

/*
Success
Details 
Runtime: 16 ms, faster than 89.42% of C++ online submissions for Binary Prefix Divisible By 5.
Memory Usage: 10.6 MB, less than 100.00% of C++ online submissions for Binary Prefix Divisible By 5.
*/