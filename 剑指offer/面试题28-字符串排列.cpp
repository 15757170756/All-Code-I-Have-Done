/*
方法一：使用STL的next_permutation
*/

#if 0
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>

using namespace::std;

template<typename T>
void permutations(vector<T>& vecIn, vector<vector<T>>& vecOut)
{
	sort(vecIn.begin(), vecIn.end());
	do {
		vecOut.emplace_back(vecIn);
	} while (next_permutation(vecIn.begin(), vecIn.end()));
}


int main()
{
	string str = "abc";
	vector<char> vecChar;
	vector<vector<char>> resultVec;
	for (int i = 0; i < str.size(); ++i)
		vecChar.emplace_back(str[i]);

	permutations(vecChar, resultVec);
	for (int i = 0; i < resultVec.size(); ++i) {
		vector<char> tempVec = resultVec[i];
		for (int j = 0; j < tempVec.size(); ++j)
			cout << tempVec[j];
		cout << endl;
	}

	return 0;
}
//Algorithm中next_permutation的实现

template<typename BidirIt>
bool my_next_permutation(BidirIt first, BidirIt last)
{
	if (first == last) return false;
	BidirIt i = last;
	if (first == --i) return false;

	while (true) {
		BidirIt i1, i2;

		i1 = i;
		if (*--i < *i1) {
			i2 = last;
			while (!(*i < *--i2));
			std::iter_swap(i, i2);
			std::reverse(i1, last);
			return true;
		}
		if (i == first) {
			std::reverse(first, last);
			return false;
		}
	}
}
#endif




/*
方法二：使用递归实现
*/
#include <iostream>

using namespace::std;

void permutation(char* str, char* pBegin)
{
	if (*pBegin == '\0')
		cout << str << endl;
	else {
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh) {
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			permutation(str, pBegin + 1);

			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}

void permutation(char* str)
{
	if (!str)
		return;

	permutation(str, str);
}

int main()
{
	char str[] = "abc";
	permutation(str);

	return 0;
}