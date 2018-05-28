/*
�����ַ�
ʱ�����ƣ�C/C++���� 2000MS���������� 4000MS
�ڴ����ƣ�C/C++���� 65536KB���������� 589824KB
��Ŀ������
��ʮ���Ʊ�ʾ�У�����һ�����������������ַ���0��-��9����ʾ������
���ǵ���0��-��9����Щ�ַ�ÿ���ַ�����������ʱ��������Щ���������޷���ʾ�����ˡ�
��������������1�� ��һ����2�� ����ô���ܱ�ʾ�� 11��12��121 �ȵȣ�
�����޷���ʾ�� 10��122��200 ������

����������ӵ��һЩ�ַ������Ƕ��ǡ�0��-��9�����ַ���
�����ѡ������һЩ�ַ�Ȼ��������ϳ�һ�����֣���ô�����޷���ɵ���С���������Ƕ��٣�

����
��һ�а���һ�����ַ���0��-��9����ɵ��ַ�������ʾ�����ʹ�õ��ַ���

�� 1 ���ַ������ȡ� 1000

���
��������޷���ɵ���С��������


��������
55

�������
1


Hint
Input Sample 2
123456789
Output Sample 2
10
*/

/*
û��������o(�i�n�i)o
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