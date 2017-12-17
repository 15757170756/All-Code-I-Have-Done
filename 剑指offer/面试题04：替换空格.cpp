
#include <iostream>
#include <cstring>
#include <string>

using namespace::std;

void replaceBlank1(char str[]);
void replaceBlank2(string& str);
void replaceBlank3(char str[], int length);

int main()
{
	char charStr[30] = "We are happy  .";
	replaceBlank1(charStr);
	cout << charStr << endl;

	char charStr3[30] = "We are happy  .";
	replaceBlank3(charStr3, 30);
	cout << charStr3 << endl;

	string stringStr = "We are happy  .";
	replaceBlank2(stringStr);
	cout << stringStr << endl;

	return 0;
}


void replaceBlank1(char str[])
{
	if (str == nullptr)
		return;

	int strLength = strlen(str);
	for (int i = 0; i < strLength; ++i) {
		if (str[i] == ' ') {
			for (int j = strLength; j >= i + 2; --j) {
				str[j + 1] = str[j - 1];
			}
			str[i] = '%';
			str[i + 1] = '2';
			str[i + 2] = '0';
			strLength += 2;
		}
	}
}


void replaceBlank2(string& str)
{
	string insertStr = "%20";
	size_t ind = 0;
	while (ind != string::npos) {
		ind = str.find(' ');
		if (ind == string::npos)
			break;
		str.erase(ind, 1);
		str.insert(ind, insertStr);
	}
}


void replaceBlank3(char str[], int length)
{
	if (str == nullptr || length <= 0)
		return;

	int originalLength = 0;
	int numberofBlank = 0;

	int i = 0;
	while (str[i] != '\0') {
		++originalLength;

		if (str[i] == ' ')
			++numberofBlank;
		++i;
	}

	int newLength = originalLength + 2 * numberofBlank;

	if (newLength >= length) {
		printf("error, overflow!");
		return;
	}

	int indexOfOringal = originalLength;
	int indexOfNew = newLength;
	while (indexOfOringal >= 0 && indexOfNew > indexOfOringal) {
		if (str[indexOfOringal] == ' ') {
			str[indexOfNew--] = '0';
			str[indexOfNew--] = '2';
			str[indexOfNew--] = '%';
		}
		else
			str[indexOfNew--] = str[indexOfOringal];

		--indexOfOringal;
	}
}

