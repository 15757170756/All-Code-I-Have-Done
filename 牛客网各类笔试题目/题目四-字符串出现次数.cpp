/*
实现find_sub_string(str1,str2)函数，判断字符串str2在str1中出现的次数。返回str2在str1中出现的次数。
int find_sub_string(const std::string& str1, const string& str2);
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
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace::std;

int find_sub_string(const std::string &str1, const string &str2)
{
	int cnt = 0;
	int n = 0;
	int i = 0;
	while (n != string::npos) {
		n = str1.find(str2, i);
		if (n == string::npos)
			break;
		i = n + 1;
		++cnt;
	}

	return cnt;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		string str1, str2;
		cin >> str1 >> str2;
		cout << find_sub_string(str1, str2) << endl;
	}

}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}