/*
https://leetcode.com/problems/relative-sort-array/

1122. Relative Sort Array
Easy

9

2

Favorite

Share
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.  Elements that don't appear in arr2 should be placed at the end of arr1 in ascending order.

 

Example 1:

Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]
 

Constraints:

arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
Each arr2[i] is distinct.
Each arr2[i] is in arr1.
*/


class Solution {
public:
	vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
		int arr1Len = arr1.size();
		int arr2Len = arr2.size();
		vector<int> res(arr1Len, 0);
		vector<int> auxVec(1001, 0);
		for (int i = 0; i < arr1Len; ++i) {
			auxVec[arr1[i]]++;
		}
		int j = 0;
		for (int i = 0; i < arr2Len; ++i) {
			while (auxVec[arr2[i]]) {
				res[j++] = arr2[i];
				--auxVec[arr2[i]];
			}
		}
		for (int i = 0; i < 1001; ++i) {
			while (auxVec[i]) {
				res[j++] = i;
				--auxVec[i];
			}
		}
		return res;
	}
};


/*
Details 
Runtime: 4 ms, faster than 66.67% of C++ online submissions for Relative Sort Array.
Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Relative Sort Array.
*/
