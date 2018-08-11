/*
85. Maximal Rectangle
DescriptionHintsSubmissionsDiscussSolution
Given a 2D binary matrix filled with 0's and 1's, 
find the largest rectangle containing only 1's and return its area.

Example:

Input:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
*/



/*
题目内容：
有个二维矩阵全由0，1组成，找出其中由1能组成的最大矩形，
并返回其面积。数组有m行，n列

思路：
1、遍历所有点，求以每个为’1’的点为左上角的所有矩形面积，并求其最大值。
时间复杂度O((mn)2).

2、参考84题的直方图中找最大矩形面积的思想
（详见LeetCode 84. Largest Rectangle in Histogram），
从上往下，从左往右遍历数组，
用一个长度为n的数组h[]记录遍历到当前列的时候的直方图高度。
相对应是个扫描的操作，从上往下从左到右扫描这个数组，
并计算当前扫描出来的直方图最大面积。

例：当遍历到上图中的matrix[2][0]等于’1’，
则此时组成的直方图为[3]，matrix[2][1]等于’1’，
此时组成的直方图为[3,1]，以此类推同时根据84题的思路，
用一个栈来存储直方图的坐标，
可以使得计算面积时每行数据只入栈出栈一次，
所以，总的时间复杂度为O(mn),空间复杂度为O(n)
*/



class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.size() < 1)
			return 0;
		int row = matrix.size();
		int col = matrix[0].size();
		int maxNum = 0;
		vector<int> h(col);
		stack<int> st;
		for (int i = 0; i < row; ++i) {
			int start = -1;
			for (int j = 0; j < col; ++j) {
				if (matrix[i][j] == '1')
					h[j]++;
				else
					h[j] = 0;
				if (st.empty()) {
					if (h[j] != 0) {
						st.push(j);
						start = j;
					}
				}
				else {
					while (!st.empty() && h[st.top()] > h[j]) {
						int l = st.top();
						st.pop();
						maxNum = max(h[l] *
							(st.empty() ? j - start : (j - 1 - st.top())), maxNum);
					}
					if (h[j] > 0)
						st.push(j);
				}
			}
			while (!st.empty()) {
				int l = st.top();
				st.pop();
				maxNum = max(h[l] *
					(st.empty() ? col - start : (col - 1 - st.top())), maxNum);
			}
		}
		return maxNum;
	}
};
