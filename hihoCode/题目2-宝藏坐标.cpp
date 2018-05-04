/*
题目2 : 宝藏坐标
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi得到了一张藏宝图。图中有一串数字字符串，小Hi分析应该是一处坐标"X,Y"，例如"13.2,20"。

可以由于藏宝图年代久远，标点符号'.'和','都消失不见了，只剩下一串数字，例如"13220"。

你能帮助小Hi从数字串还原出所有可能的坐标吗？

合法的X或Y应满足：

1. 是一个整数或小数。

2. 没有多余的0。例如"03"，"0.10", "00.2", "1.0"都不合法。

3. 小数点不能在首尾。例如".2", "2."都不合法。

输入
一个数字字符串，长度不超过6。

输入保证有解。

输出
所有可能的坐标，每个一行。

按X从小到大输出；如果X相同，按Y从小到大输出。

样例输入
13220
样例输出
1,3220
1.3,220
1.32,20
1.322,0
13,220
13.2,20
13.22,0
132,20
132.2,0
1322,0
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>

using namespace::std;

void split(const string &s, const char delim, vector<string> &resultStr)
{
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		if (item.length() > 0)
			resultStr.push_back(item);
}

bool cmp(const string &s1, const string &s2)
{
	vector<string> ss1, ss2;
	split(s1, ',', ss1);
	split(s2, ',', ss2);
	float x1, y1, x2, y2;
	x1 = stof(ss1[0]);
	y1 = stof(ss1[1]);
	x2 = stof(ss2[0]);
	y2 = stof(ss2[1]);
	if (x1 < x2)
		return true;
	if (x1 == x2)
		return y1 < y2;
	return false;
}

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	string s;
	cin >> s;
	vector<string> vecStr;
	for (int i = 1; i < s.size(); ++i) {
		string temp = s;
		temp.insert(i, 1, ',');
		vecStr.emplace_back(temp);
	}
	vector<string> dotVec;
	for (int i = 0; i < vecStr.size(); ++i) {
		string temp = vecStr[i];
		for (int j = 1; j < temp.size(); ++j) {
			string ttmp = temp;
			if (ttmp[j] == ',') {
				++j;
				continue;
			}
			ttmp.insert(j, 1, '.');
			bool flag = false;
			for (int k = j; k < ttmp.size(); ++k) {
				if (ttmp[k] == '0') {
					flag = true;
					break;
				}
				if (ttmp[k] == ',')
					break;
			}
			if (flag == false)
				dotVec.emplace_back(ttmp);
		}
	}
	for (int i = 0; i < dotVec.size(); ++i)
		vecStr.emplace_back(dotVec[i]);

	sort(vecStr.begin(), vecStr.end(), cmp);
	for (int i = 0; i < vecStr.size(); ++i)
		cout << vecStr[i] << endl;

	return 0;
}
/*
wrong
*/

















#include <bits/stdc++.h>
using namespace std;

vector<string> cal(string s)
{
	int l = s.length();
	vector<string> ret;
	if (l == 1 && s[0] == '0' 
		|| s[0] != '0')
		ret.push_back(s);
	for (int i = l - 1; i > 0; --i){
		if (s[l - 1] != '0' 
			&& (s[0] != '0'|| i == 1)) 
			ret.push_back(s.substr(0, i) + '.' + s.substr(i, l - i));
	}
	return ret;
}

typedef pair<string, string> pii;
vector<pii> ans;

int main()
{
	char s[11];
	scanf("%s", s);
	int l = strlen(s);
	for (int i = 0; i < l - 1; ++i){
		string a = string(s).substr(0, i + 1);
		string b = string(s).substr(i + 1);
		vector<string> v1 = cal(a), v2 = cal(b);
		for (int j = v1.size() - 1; j >= 0; j--)
			for (int k = v2.size() - 1; k >= 0; k--)
				ans.push_back(pii(v1[j], v2[k]));
	}
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); ++i) 
		cout << ans[i].first << ',' << ans[i].second << endl;
	return 0;
}