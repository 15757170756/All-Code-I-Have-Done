#include <iostream>
#include <cstring>
#include <cmath>

using namespace::std;

int getCols(const char* alphaCode)
{
	int result = 0;
	int strLength = strlen(alphaCode);
	for (int i = 0; i < strLength; ++i) {
		int temp = (alphaCode[i] - '0' - 16) * pow(26, strLength - 1 - i);
		result += temp;
	}

	return result;
}

int main()
{
	char a[] = "ABZ";
	int result = getCols(a);
	cout << result << endl;

	return 0;
}