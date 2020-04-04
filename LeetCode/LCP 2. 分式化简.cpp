/*
LCP 2. 分式化简




题目描述
评论 (44)
题解(45)
提交记录
有一个同学在学习分式。他需要将一个连分数化成最简分数，你能帮助他吗？



连分数是形如上图的分式。在本题中，所有系数都是大于等于0的整数。

 

输入的cont代表连分数的系数（cont[0]代表上图的a0，以此类推）。返回一个长度为2的数组[n, m]，使得连分数的值等于n / m，且n, m最大公约数为1。

 

示例 1：

输入：cont = [3, 2, 0, 2]
输出：[13, 4]
解释：原连分数等价于3 + (1 / (2 + (1 / (0 + 1 / 2))))。注意[26, 8], [-13, -4]都不是正确答案。
示例 2：

输入：cont = [0, 0, 3]
输出：[3, 1]
解释：如果答案是整数，令分母为1即可。
限制：

cont[i] >= 0
1 <= cont的长度 <= 10
cont最后一个元素不等于0
答案的n, m的取值都能被32位int整型存下（即不超过2 ^ 31 - 1）。
*/


class Solution {
public:
	vector<int> fraction(vector<int>& cont) {
		vector<int> res(2, 0);
		if (cont.size() == 1) {
			res[0] = cont[0];
			res[1] = 1;
			return res;
		}
		int denominator, numerator;
		reverse(cont.begin(), cont.end());
		for (int i = 0; i < cont.size() - 1; ++i) {
			if (i == 0) {
				denominator = cont[i];
				numerator = denominator*cont[i + 1] + 1;
			}
			else {
				numerator = denominator*cont[i + 1] + numerator;
			}
			if (i < cont.size() - 2) {
				int temp = denominator;
				denominator = numerator;
				numerator = temp;
			}
		}
		res[0] = numerator;
		res[1] = denominator;

		return res;
	}
};


/*
执行结果：
通过
显示详情
执行用时 :
0 ms
, 在所有 cpp 提交中击败了
100.00%
的用户
内存消耗 :
8.2 MB
, 在所有 cpp 提交中击败了
100.00%
的用户
炫耀一下:
*/