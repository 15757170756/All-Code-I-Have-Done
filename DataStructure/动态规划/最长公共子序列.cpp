#include <iostream>
#include <string>
#include <vector>

using namespace::std;

int lcs(const string s1, const string s2, vector<vector<int>>& vec);
void print_lcs(vector<vector<int>>& vec, string str, int i, int j);

int main(int argc, char* argv[])
{
	const string str1 = "abcdefg";
	const string str2 = "abdgt";
	vector<vector<int>> vec1(str1.size() + 1, vector<int>(str2.size() + 1, -1));
	int result = lcs(str1, str2, vec1);
	cout << "result = " << result << endl;
	print_lcs(vec1, str1, str1.size(), str2.size());
	cout << endl;

	getchar();
	return 0;
}



/*
最长公共子序列
*/
int lcs(const string str1, const string str2, vector<vector<int>>& vec)
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
				vec[i][j] = 0;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				vec[i][j] = 1;
			}
			else {
				c[i][j] = c[i][j - 1];
				vec[i][j] = 2;
			}
		}
	}

	return c[len1][len2];
}

void print_lcs(vector<vector<int>>& vec, string str, int i, int j)
{
	if (i == 0 || j == 0)
		return;

	if (vec[i][j] == 0) {
		print_lcs(vec, str, i - 1, j - 1);
		cout << str[i - 1];
	}
	else if (vec[i][j] == 1)
		print_lcs(vec, str, i - 1, j);
	else
		print_lcs(vec, str, i, j - 1);
}
















#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <limits>
#include <climits>

using namespace::std;

int lcs(const string &s1, const string &s2, vector<vector<int>> &auxVec)
{
	int s1Length = s1.size();
	int s2Length = s2.size();
	if (s1Length < 1 || s2Length < 1)
		return 0;
	vector<vector<int>> c(s1Length + 1, vector<int>(s2Length + 1));
	auxVec.assign(s1Length + 1, vector<int>(s2Length + 1));

	for (int i = 1; i <= s1Length; ++i) {
		for (int j = 1; j <= s2Length; ++j) {
			if (s1[i - 1] == s2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				auxVec[i][j] = 0;
			}
			else if (c[i - 1][j] > c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				auxVec[i][j] = 1;
			}
			else {
				c[i][j] = c[i][j - 1];
				auxVec[i][j] = 2;
			}
		}
	}

	for (int i = 0; i < s1Length + 1; ++i) {
		for (int j = 0; j < s2Length + 1; ++j)
			cout << c[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < s1Length + 1; ++i) {
		for (int j = 0; j < s2Length + 1; ++j)
			cout << auxVec[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	return c[s1Length][s2Length];
}

void printLCS(vector<vector<int>> &auxVec, const string &s1,
	int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (auxVec[i][j] == 0) {
		printLCS(auxVec, s1, i - 1, j - 1);
		cout << s1[i - 1];
	}
	else if (auxVec[i][j] == 1)
		printLCS(auxVec, s1, i - 1, j);
	else
		printLCS(auxVec, s1, i, j - 1);
}

int main()
{
	string str1 = "abcdefg";
	string str2 = "abdgt";
	vector<vector<int>> auxVec;
	int result = lcs(str1, str2, auxVec);
	cout << result << endl;
	printLCS(auxVec, str1, str1.size(), str2.size());
	return 0;
}