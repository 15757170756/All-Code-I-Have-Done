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

void scanDigits(char **str)
{
	while (**str != '\0' && **str >= '0'
		&& **str <= '9')
		++(*str);
}

bool isExponential(char **str)
{
	if (**str != 'e' && **str != 'E')
		return false;

	++(*str);
	if (**str == '+' || **str == '-')
		++(*str);

	if (**str == '\0')
		return false;

	scanDigits(str);

	return (**str == '\0') ? true : false;
}

bool isNumeric(char *str)
{
	if (str == nullptr)
		return false;
	if (*str == '+' || *str == '-')
		++str;
	if (*str == '\0')
		return false;

	bool numeric = true;
	scanDigits(&str);
	if (*str != '\0') {
		if (*str == '.') {
			++str;
			scanDigits(&str);

			if (*str == 'e' || *str == 'E')
				numeric = isExponential(&str);
		}
		else if (*str == 'e' || *str == 'E')
			numeric = isExponential(&str);
		else
			numeric = false;
	}

	return numeric && *str == '\0';
}

void test()
{
	char *str1 = "+100";
	char *str2 = "5e4";
	char *str3 = "1e3.24";
	char *str4 = "-1E-16";
	char *str5 = "+-5";
	char *str6 = "12e";
	cout << boolalpha;
	cout << isNumeric(str1) << endl;
	cout << isNumeric(str2) << endl;
	cout << isNumeric(str3) << endl;
	cout << isNumeric(str4) << endl;
	cout << isNumeric(str5) << endl;
	cout << isNumeric(str6) << endl;

}

int main(int argc, char* argv[])
{
	test();

	return 0;
}




