/*
https://leetcode.com/problems/zigzag-conversion/

6. ZigZag Conversion
Medium

965

2950

Favorite

Share
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*/

class Solution {
public:
	string convert(string s, int numRows) {
		int len = s.size();
		if (len < 2 || numRows == 1)
			return s;
		string res;
		int nums = 2 * numRows - 2;
		for (int i = 0; i < numRows; ++i) {
			int tempInter = nums - 2 * i;
			int j = i;
			if (tempInter == 0)
				tempInter = nums;
			while (j < len) {
				res.push_back(s[j]);
				j += tempInter;
				tempInter = nums - tempInter;
				if (tempInter == 0)
					tempInter = nums;
			}
		}
		return res;
	}
};

/*
Success
Details 
Runtime: 12 ms, faster than 99.89% of C++ online submissions for ZigZag Conversion.
Memory Usage: 10.2 MB, less than 99.79% of C++ online submissions for ZigZag Conversion.
*/