/*
https://leetcode.com/problems/convert-to-base-2/

1017. Convert to Base -2
Medium

43

74

Favorite

Share
Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).

The returned string must have no leading zeroes, unless the string is "0".

 

Example 1:

Input: 2
Output: "110"
Explantion: (-2) ^ 2 + (-2) ^ 1 = 2
Example 2:

Input: 3
Output: "111"
Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
Example 3:

Input: 4
Output: "100"
Explantion: (-2) ^ 2 = 4
 

Note:

0 <= N <= 10^9
Accepted
4,165
Submissions
7,566
Seen this question in a real interview before?
*/

class Solution {
public:
	string baseNeg2(int N) {
		string res = "";
		while (N) {
			int a = abs(N % (-2));
			res = (a == 0 ? '0' : '1') + res;
			N = (N - a) / (-2);
		}
		return res == "" ? "0" : res;
	}
};

/*
Success
Details 
Runtime: 4 ms, faster than 100.00% of C++ online submissions for Convert to Base -2.
Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Convert to Base -2.
*/