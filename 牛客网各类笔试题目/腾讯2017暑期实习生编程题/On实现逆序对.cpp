/*
由于输入固定为ABCD四个字母，可以多个
这样借用计数排序的思想。
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace::std;

int inversePairs(string &s)
{
	int auxArr[4];
	memset(auxArr, 0, sizeof(auxArr));
	for (int i = 0; i < s.size(); ++i) {
		int index = s[i] - 'A';
		++auxArr[index];
	}

	//for (int i = 0; i < 3; ++i)
	//	auxArr[i + 1] += auxArr[i];

	int sum = 0;
	for (int i = s.size() - 1; i >= 0; --i) {
		int index = s[i] - 'A';
		int j;
		for (j = index + 1; j < 4; ++j) {
			sum += auxArr[j];
		}
		--auxArr[index];
	}

	return sum;
}

int main()
{
	string s = "DBBACDABC";
	cout << inversePairs(s) << endl;

	return 0;
}