/*
Given n non-negative integers representing the histogram's bar height
 where the width of each bar is 1, find the area of largest rectangle 
 in the histogram.
Above is a histogram where width of each bar is 1, 
given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.
Example:

Input: [2,1,5,6,2,3]
Output: 10

https://mp.weixin.qq.com/s/0-K92NVdJa7cJ-qvaiz6oQ
*/





/*
设定从左往右遍历数组。
以横轴为长，纵轴为宽，那么每个长方形区域 [l, r] 的宽一定为 min(heights[i:j])
对于任意一个柱条heights[i]，如果它的右边有一个x>i并且heights[x]<heights[i]，
以这个柱条高度d为宽的最大长方形区域的右边界一定小于x，
或者说，所以当从左往右遍历时，每当遍历的当前高度比之前出现的柱条高度低时，
就可以计算以之前的柱条为高的最大方形区域面积。

方法：用栈存储之前遍历的所有柱条横坐标，
每当当前遍历的柱条heights[i]比栈顶端的矮时，出栈，计算出栈元素的长方体的最大面积，
最大面积由如下边界构成：左边界为新的栈顶元素，右边界为当前遍历的 i 。
每个数据只会栈栈中入栈出栈一次，所以时间复杂度为O(n)。
*/
class Solution {
public:
	int largestRectangleArea(vector<int>& heights) {
		int len = heights.size();
		stack<int> st;
		int maxArea = 0;
		for (int i = 0; i <= len; ++i) {
			int h = (i == len ? 0 : heights[i]);
			if (st.empty() || h >= heights[st.top()])
				st.push(i);
			else {
				int tp = st.top();
				st.pop();
				maxArea = max(maxArea,
					heights[tp] * (st.empty() ? i : i - 1 - st.top()));
				--i;
			}
		}
		return maxArea;
	}
};