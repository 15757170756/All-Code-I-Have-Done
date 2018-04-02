#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;

const int g_MAXNUMBERLENGTH = 10;
char *g_strCombine1 = new char[g_MAXNUMBERLENGTH * 2 + 1];
char *g_strCombine2 = new char[g_MAXNUMBERLENGTH * 2 + 1];

int compare(const void *strNumber1, const void *strNumber2)
{
	strcpy(g_strCombine1, *(const char**)strNumber1);
	strcat(g_strCombine1, *(const char**)strNumber2);

	strcpy(g_strCombine2, *(const char**)strNumber2);
	strcat(g_strCombine2, *(const char**)strNumber1);

	return strcmp(g_strCombine1, g_strCombine2);
}

void printMinNumber(int *numbers, int length)
{
	assert(numbers != nullptr && length > 0);

	char **strNumbers = (char**)(new int[length]);
	for (int i = 0; i < length; ++i) {
		strNumbers[i] = new char[g_MAXNUMBERLENGTH + 1];
		sprintf(strNumbers[i], "%d", numbers[i]);
	}

	qsort(strNumbers, length, sizeof(char*), compare);
	for (int i = 0; i < length; ++i)
		printf("%s", strNumbers[i]);
	printf("\n");

	for (int i = 0; i < length; ++i)
		delete[] strNumbers[i];
	delete[] strNumbers;
}

int main(int argc, char* argv[])
{
	int arr[] = { 3, 32, 321 };
	int length = sizeof(arr) / sizeof(arr[0]);
	printMinNumber(arr, length);

	return 0;
}


















#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <sstream>

using namespace::std;

bool compare(const string &s1, const string &s2)
{
	return ((s1 + s2) < (s2 + s1));
}

void printMinNumber(vector<int> &vec)
{
	int length = vec.size();
	assert(length > 0);

	vector<string> vecStr(length);
	for (int i = 0; i < length; ++i)
		vecStr[i] = to_string(vec[i]);

	sort(vecStr.begin(), vecStr.end(), compare);

	for (int i = 0; i < length; ++i)
		cout << vecStr[i];
	cout << endl;
}

int main(int argc, char* argv[])
{
	vector<int> vec = { 3, 32, 321, 2 };
	printMinNumber(vec);

	return 0;
}
