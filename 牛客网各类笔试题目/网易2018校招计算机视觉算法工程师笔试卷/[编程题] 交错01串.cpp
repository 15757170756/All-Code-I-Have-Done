/*
[编程题] 交错01串
时间限制：1秒

空间限制：32768K

如果一个01串任意两个相邻位置的字符都是不一样的,
我们就叫这个01串为交错01串。例如: "1","10101","0101010"都是交错01串。
小易现在有一个01串s,小易想找出一个最长的连续子串,
并且这个子串是一个交错01串。
小易需要你帮帮忙求出最长的这样的子串的长度是多少。 
输入描述:
输入包括字符串s,s的长度length(1 ≤ length ≤ 50),
字符串中只包含'0'和'1'


输出描述:
输出一个整数,表示最长的满足要求的子串长度。

输入例子1:
111101111

输出例子1:
3
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	string s;
	cin >> s;
	string subStr = "01";
	string result;
	vector<string> vecStr;
	int cnt = 0, maxCnt = -1, tmp = 0;
	for (int i = 0; i < s.size();) {
		int idx = s.find(subStr, i);
		if (i == 0 && idx == string::npos) {
			cout << 1 << endl;
			return 0;
		}
		if (idx - tmp != 2 && i != 0) {
			vecStr.push_back(result);
			result.clear();
			cnt = 0;
		}
		if (idx != string::npos) {
			cnt += 2;
			i = idx + 1;
			result.append("01");
		}
		tmp = idx;
		if (idx == string::npos)
			break;
		//maxCnt = max(maxCnt, cnt);
	}
	int maxLen = -1;
	string maxLenStr;
	for (int j = 0; j < vecStr.size(); ++j) {
		//cout << maxLen << ' ' << vecStr[j].size() << endl;
		if (maxLen < (int)vecStr[j].size()) {
			maxLen = vecStr[j].size();
			maxLenStr = vecStr[j];
		}
	}
	cnt = 0;
	int idx = s.find(maxLenStr, 0);
	if (idx > 0 && s[idx - 1] == '1')
		++cnt;
	int lastIdx = idx + maxLenStr.size();
	if (lastIdx < s.size() && s[lastIdx] == '0')
		++cnt;
	cout << cnt + maxLenStr.size() << endl;

	return 0;
}

/*
哎，这个题目都困扰我了好久的。。。
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为90.00%

测试用例:
0101100111011110101000

对应输出应该为:

6

你的输出为:

4
*/








#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	string s;
	cin >> s;
	string subStr = "01";
	string result;
	vector<pair<string, int>> vecStr;
	int cnt = 0, maxCnt = -1, tmp = 0;
	vector<int> extCnt;
	for (int i = 0; i < s.size();) {
		int idx = s.find(subStr, i);
		if (i == 0 && idx == string::npos) {
			cout << 1 << endl;
			return 0;
		}
		if (idx - tmp != 2 && i != 0) {
			vecStr.emplace_back(result, tmp - result.size() + 2);
			result.clear();
			cnt = 0;
		}
		if (idx != string::npos) {
			cnt += 2;
			i = idx + 1;
			result.append("01");
		}
		tmp = idx;
		if (idx == string::npos)
			break;
		//maxCnt = max(maxCnt, cnt);
	}
	int maxLen = -1;
	string maxLenStr;
	int maxLenIdx;
	for (int j = 0; j < vecStr.size(); ++j) {
		maxLenStr = vecStr[j].first;
		maxLenIdx = vecStr[j].second;

		cnt = 0;
		int idx = s.find(maxLenStr, maxLenIdx);
		if (idx > 0 && s[idx - 1] == '1')
			++cnt;
		int lastIdx = idx + maxLenStr.size();
		if (lastIdx < s.size() && s[lastIdx] == '0')
			++cnt;
		
		maxLen = max(maxLen, (int)(cnt + maxLenStr.size()));
	}

	cout << maxLen << endl;

	return 0;
}

/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/