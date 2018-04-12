#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;


/*
注意空指针、空字符串以及数据范围
*/
int strToInt(char *str)
{
	assert(str != nullptr);
	long long result = 0;
	int len = strlen(str);
	if (len == 0)
		return result;

	int flag = 1;
	char *temp = str;

	while (isspace(*temp))
		++temp;
	if (*temp == '-') {
		flag = -1;
		++temp;
	}
	else if (*temp == '+')
		++temp;
	for (char *i = temp; *i != '\0'
		&& (*i >= '0' && *i <= '9'); ++i) {
		result = result * 10 + flag * (*i - '0');
		if (result >= INT_MAX)
			return INT_MAX;
		else if (result <= INT_MIN)
			return INT_MIN;
	}

	return result;
}

enum Status { kValid = 0, kInvalid };

int g_nStatus = kValid;

long long StrToIntCore(const char *digit, bool minus)
{
	long long num = 0;
	while (*digit != '\0') {
		if (*digit >= '0' && *digit <= '9') {
			int flag = minus ? -1 : 1;
			num = num * 10 + flag*(*digit - '0');

			if ((!minus && num > 0x7FFFFFFF)
				|| (minus && num < (signed int)0x80000000)) {
				num = 0;
				break;
			}
			++digit;
		}
		else {
			num = 0;
			break;
		}
	}

	if (*digit == '\0')
		g_nStatus = kValid;

	return num;
}

int StrToInt(const char *str)
{
	g_nStatus = kInvalid;
	long long num = 0;

	if (str != nullptr && *str != '\0') {
		bool minus = false;
		if (*str == '+')
			++str;
		else if (*str == '-') {
			++str;
			minus = true;
		}
		if (*str != '\0')
			num = StrToIntCore(str, minus);
	}

	return (int)num;
}

int main(int argc, char* argv[])
{

	char s[90] = "";
	cin >> s;
	cout << atoi(s) << endl;
	cout << strToInt(s) << endl;
	cout << StrToInt(s) << endl;

	cout << INT_MAX << endl;

	char *ss = nullptr;
	//cout << atoi(ss) << endl;
	//cout << strToInt(ss) << endl;
	return 0;
}




