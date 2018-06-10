/*
845. Longest Mountain in Array
User Accepted: 944
User Tried: 1188
Total Accepted: 953
Total Submissions: 3308
Difficulty: Medium
Let's call any (contiguous) subarray B (of A) a mountain
 if the following properties hold:

B.length >= 3
There exists some 0 < i < B.length - 1 
such that B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
(Note that B could be any subarray of A, including the entire array A.)

Given an array A of integers, return the length of the longest mountain. 

Return 0 if there is no mountain.

 

Example 1:

Input: [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
Example 2:

Input: [2,2,2]
Output: 0
Explanation: There is no mountain.
 

Note:

0 <= A.length <= 10000
0 <= A[i] <= 10000
*/

//two pointers
class Solution {
public:
	int longestMountain(vector<int>& A) {
		int ans = 0;
		for (int k = 1, i = k, j = k, n = (int)A.size();
			k < n - 1; ++k, i = k, j = k) {
			while (i > 0 && A[i - 1] < A[i])
				--i;
			while (j < n - 1 && A[j] > A[j + 1])
				++j;
			if (i != k && j != k)
				ans = max(ans, j - i + 1);
		}
		return ans;
	}
};
//O(n^2)time complex
//Submission Result: Accepted 



int longestMountain(vector<int> A) {
    int N = A.size(), res = 0;
    vector<int> up(N, 0), down(N, 0);

    for (int i = N - 2; i >= 0; --i) 
    	if (A[i] > A[i + 1])
    		down[i] = down[i + 1] + 1;

    for (int i = 0; i < N; ++i) {
        if (i > 0 && A[i] > A[i - 1]) 
        	up[i] = up[i - 1] + 1;
        if (up[i] && down[i]) 
        	res = max(res, up[i] + down[i] + 1);
    }
    return res;
}
//O(n) time complex,O(n) space complex
//Submission Result: Accepted 