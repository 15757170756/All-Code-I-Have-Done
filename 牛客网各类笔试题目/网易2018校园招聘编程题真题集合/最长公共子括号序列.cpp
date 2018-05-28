/*
时间限制：1秒

空间限制：100768K

一个合法的括号匹配序列被定义为:
1. 空串""是合法的括号序列
2. 如果"X"和"Y"是合法的序列,那么"XY"也是一个合法的括号序列
3. 如果"X"是一个合法的序列,那么"(X)"也是一个合法的括号序列
4. 每个合法的括号序列都可以由上面的规则生成
例如"", "()", "()()()", "(()())", "(((()))"都是合法的。
从一个字符串S中移除零个或者多个字符得到的序列称为S的子序列。
例如"abcde"的子序列有"abe","","abcde"等。
定义LCS(S,T)为字符串S和字符串T最长公共子序列的长度,
即一个最长的序列W既是S的子序列也是T的子序列的长度。
小易给出一个合法的括号匹配序列s,小易希望你能找出具有以下特征的括号序列t:
1、t跟s不同,但是长度相同
2、t也是一个合法的括号匹配序列
3、LCS(s, t)是满足上述两个条件的t中最大的
因为这样的t可能存在多个,小易需要你计算出满足条件的t有多少个。

如样例所示: s = "(())()",跟字符串s长度相同的合法括号匹配序列有:
"()(())", "((()))", "()()()", "(()())",其中LCS( "(())()", "()(())" )为4,
其他三个都为5,所以输出3.
输入描述:
输入包括字符串s(4 ≤ |s| ≤ 50,|s|表示字符串长度),保证s是一个合法的括号匹配序列。


输出描述:
输出一个正整数,满足条件的t的个数。

输入例子1:
(())()

输出例子1:
3
*/


#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

# define MAX_SIZE 100

using namespace std;

struct CountAndValue
{
	int count;
	int value;
};

int lcs(const string str1, const string str2)
{
	int len1 = str1.size();
	int len2 = str2.size();
	if (len1 == 0 || len2 == 0)
		return 0;
	vector<vector<int>> c(len1 + 1, vector<int>(len2 + 1, 0));
	for (int i = 1; i <= len1; ++i) {
		for (int j = 1; j <= len2; ++j) {
			if (str1[i - 1] == str2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];
			}
		}
	}

	return c[len1][len2];
}

void _getParenthesis(int pos, int n, int open, int close, vector<string>& resultVec);

// Wrapper over _printParenthesis()
void getParenthesis(int n, vector<string>& resultVec)
{
	if (n > 0)
		_getParenthesis(0, n, 0, 0, resultVec);
	return;
}

void _getParenthesis(int pos, int n, int open, int close, vector<string>& resultVec)
{
	static char str[MAX_SIZE];

	if (close == n)
	{
		resultVec.push_back(str);
		//printf("%s \n", str);
		return;
	}
	else
	{
		if (open > close)
		{
			str[pos] = ')';
			_getParenthesis(pos + 1, n, open, close + 1, resultVec);
		}

		if (open < n)
		{
			str[pos] = '(';
			_getParenthesis(pos + 1, n, open + 1, close, resultVec);
		}
	}
}

int main()
{
	string s;// = "(((())))";
	cin >> s;
	int len = s.size();
	vector<string> vecStr;
	getParenthesis(len / 2, vecStr);
	vecStr.erase(remove(vecStr.begin(), vecStr.end(), s), vecStr.end());

	//for (int i = 0; i < vecStr.size(); ++i)
	//	cout << vecStr[i] << endl;

	vector<int> vecNum;
	for (int i = 0; i < vecStr.size(); ++i) {
		int temp = lcs(s, vecStr[i]);
		vecNum.push_back(temp);
	}
	sort(vecNum.begin(), vecNum.end());
	int resultNum = count(vecNum.begin(), vecNum.end(),
		vecNum[vecNum.size() - 1]);
	cout << resultNum << endl;

	return 0;
}

/*
您的代码已保存
内存超限:您的程序使用了超过限制的内存
case通过率为50.00%
*/























/*
据题意，要想使得 LCS 最大，
删去任意一个字符即可获得 LCS = |s| - 1 ，
再把该字符插到与原来不同的任意位置可以维持原长度，
而不影响 LCS 的计算。
因此最暴力的做法是枚举每个字符，
把它插入到任意位置，判合法，去重，累计。

优化 1 ：插入是插到指定位置的字符之前，
如果插入的字符和该位置的字符相同，
则插入后还是原字符串，可以跳过这种情况。
否则最后的结果要 - 1 。
优化 2 ：左右两边一定是左右括号，
不用移动它们。但字符却可以插到它们的后面。
判合法：实际上就是括号匹配的平衡性。
在这里，如果我们从前到后遍历，
左括号可以暂时多于右括号，但不可以少于，
因为能够闭合右括号的左括号都在左边了。
每次成功闭合一对括号把数量 - 1 ，得到负数说明不平衡。
*/
#include <stdio.h>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>

using namespace std;

bool isLegal(const string& s)
{
	int cnt = 0;
	for (int i = 0; s[i]; ++i) {
		s[i] == '(' ? ++cnt : --cnt;
		if (cnt < 0) {
			return false;
		}
	}
	return true;
}

int main()
{
	string str;// = "((()))";
	cin >> str;
	set<string> record;
	for (int i = 1; i < str.size() - 1; ++i) {
		string tmp = str;
		tmp.erase(i, 1);
		for (int j = 1; j < str.size(); ++j) {
			if (str[i] == str[j]) 
				continue;
			string s(tmp);
			s.insert(j, 1, str[i]);
			if (isLegal(s)) {
				record.insert(s);
			}
		}
	}
	cout << record.size() << endl;

	return 0;
}