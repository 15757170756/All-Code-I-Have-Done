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