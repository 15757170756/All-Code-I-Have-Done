/*
976. Largest Perimeter Triangle
Easy

37

4

Favorite

Share
Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

If it is impossible to form any triangle of non-zero area, return 0.

 

Example 1:

Input: [2,1,2]
Output: 5
Example 2:

Input: [1,2,1]
Output: 0
Example 3:

Input: [3,2,3,4]
Output: 10
Example 4:

Input: [3,6,2,3]
Output: 8
 

Note:

3 <= A.length <= 10000
1 <= A[i] <= 10^6
Accepted
4,141
Submissions
7,462
*/

class Solution {
public:
	int largestPerimeter(vector<int>& A) {
		int lens = A.size();
		if (lens < 3)
			return 0;
		sort(A.begin(), A.end());
		for (int i = lens - 1; i >= 2; --i) {
			int a = A[i], b = A[i - 1], c = A[i - 2];
			if (a + b > c && a + c > b && b + c > a)
				return a + b + c;
		}
		return 0;
	}
};

/*
Success
Details 
Runtime: 60 ms, faster than 40.00% of C++ online submissions 
for Largest Perimeter Triangle.
*/