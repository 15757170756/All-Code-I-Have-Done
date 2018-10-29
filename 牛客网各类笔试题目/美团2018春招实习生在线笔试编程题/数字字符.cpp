/*
题目描述： 
在十进制表示中，任意一个正整数都是可以用字符’0’—‘9’表示出来。
但是当’0’—‘9’这些字符每种字符的数量都是有限时，可能有些正整数就无法表示出来了。
比如你有两个‘1’，一个‘2’，那么你能表示出11,12,121等等，但是你无法表示10,122,200等数。
现在你手上拥有一些字符，它们都是’0’—‘9’的字符。
你可以选出其中一些字符然后将它们组合成一个数字，那么你所无法组成的最小正整数是多少？

样例输入： 
55 
样例输出： 
1


Hint
Input Sample 2
123456789
Output Sample 2
10
*/


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <fstream>

using namespace::std;

bool cmp(const pair<char, int> & pair1, const pair<char, int> & pair2)
{

	if (pair1.second == pair2.second)
		return pair1.first < pair2.first;
	else
		return (pair1.second < pair2.second);
}

int func(string &s)
{
	vector<int> vec;
	vector<pair<char, int>> vecPair;
	for (char i = '0'; i <= '9'; ++i) {
		int temp = count(s.begin(), s.end(), i);
		//vec.push_back(temp);
		vecPair.emplace_back(i, temp);
	}
	vector<pair<char, int>> vecPairSorted = vecPair;
	sort(vecPairSorted.begin(), vecPairSorted.end(), cmp);

	for (int i = 0; i < vecPair.size(); ++i)
		cout << vecPair[i].first << ' ' << vecPair[i].second << endl;
	cout << endl;

	for (int i = 0; i < vecPairSorted.size(); ++i)
		cout << vecPairSorted[i].first << ' ' << vecPairSorted[i].second << endl;
	cout << endl;

	if (vecPair[0].second == 0) {
		for (int i = 1; i < vecPairSorted.size(); ++i) {
			if (0 == vecPairSorted[i].second)
				return vecPairSorted[i].first - '0';
		}
		return 10;
	}

	else {
		if (vecPairSorted[0].first == '0') {
			int num = vecPairSorted[1].first - '0';
			int times = vecPairSorted[1].second;
			int sum = num;
			for (int i = 0; i < times; ++i)
				sum = sum * 10 + num;
			return sum;
		}
		else {
			int num = vecPairSorted[0].first - '0';
			int times = vecPairSorted[0].second;
			int sum = num;
			for (int i = 0; i < times; ++i)
				sum = sum * 10 + num;
			return sum;
		}
	}

	return 0;
}



int main()
{
	while (1) {
		//ifstream in("input.txt");
		string s;
		//in >> s;
		cin >> s;
		cout << func(s) << endl << endl;
	}
}



























#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (string str; cin >> str;) {
		vector<int> used(10, 0);
		int digit = -1, theMin = 0x3f3f3f3f;
		for (auto it = str.begin(); it != str.end(); ++it)
			++used[*it - '0'];
		for (int i = 1; i < 10; i++)
			if (theMin > used[i])
				theMin = used[i], digit = i;
		if (used[0] + 1 <= theMin)
			cout << "1" + string(used[0] + 1, '0') << endl;
		else
			cout << string(theMin + 1, digit + '0') << endl;
	}
	return 0;
}