#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>

using namespace::std;

bool matchCore(char *str, char *pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return true;
	if (*str != '\0' && *pattern == '\0')
		return false;

	if (*(pattern + 1) == '*') {
		if (*pattern == *str
			|| (*pattern == '.' && *str != '\0'))
			return matchCore(str + 1, pattern + 2)
			|| matchCore(str + 1, pattern)
			|| matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);
	}
	if (*str == *pattern
		|| (*pattern == '.' && *str != '\0'))
		return matchCore(str + 1, pattern + 1);

	return false;
}

bool isMatch(char *str, char *pattern)
{
	if (str == nullptr || pattern == nullptr)
		return false;
	return matchCore(str, pattern);
}

void test()
{
	char *str = "aaa";
	char *pattern1 = "a.a";
	char *pattern2 = "ab*ac*a";
	char *pattern3 = "aa.a";
	char *pattern4 = "ab*a";
	char *pattern5 = "ba*ab";
	cout << boolalpha;
	cout << isMatch(str, pattern1) << endl;
	cout << isMatch(str, pattern2) << endl;
	cout << isMatch(str, pattern3) << endl;
	cout << isMatch(str, pattern4) << endl;
	cout << isMatch(str, pattern5) << endl;
}

int main(int argc, char* argv[])
{
	test();

	return 0;
}