#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;



int main(int argc, char* argv[])
{
	freopen("input.txt", "r", stdin);
	string s;
	cin >> s;
	int rows = s.size() / 16;
	vector<string> vecStr;
	for (int i = 0, j = 0; i < rows; ++i, j += 16) {
		string &temp = s.substr(j, 16);
		vecStr.emplace_back(temp);
	}
	int bias = 16;
	for (int i = 0; i < rows; ++i) {
		printf("%08x  ", bias*i);
		string &temp = vecStr[i];
		for (int j = 0; j < temp.size(); ++j) {
			if (j == 7 || j == 15)
				printf("%x  ", (int)temp[j]);
			else
				printf("%x ", (int)temp[j]);
		}
		printf("%s\n", temp.c_str());
	}

	return 0;
}