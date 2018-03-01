/*
还是有些复杂的，至少考虑的东西
蛮多的。
使我认识到了，数组名是指针常量，
即int a[10]; 
a++操作是错误的，
*/

#include <iostream>

using namespace::std;

char* myStrcpy(char* dst, const char* src)
{
	char* cp = dst;
	while (*cp++ = *src++);

	return (dst);
}

char decToHex(int dec)
{
	if (dec >= 0 && dec <= 9)
		return (dec + '0');
	else {
		switch (dec)
		{
		case 10:
			return 'A';
		case 11:
			return 'B';
		case 12:
			return 'C';
		case 13:
			return 'D';
		case 14:
			return 'E';
		case 15:
			return 'F';
		default:
			break;
		}
	}
}

void swapChar(char& c1, char& c2)
{
	char temp = c1;
	c1 = c2;
	c2 = temp;
}

/*
16进制与10进制相互转化，
输入
str：0x12，表示输入为16进制，
则转化为10进制18保存在convertedStr；
如输入为18，表示输入为16进制，
则转化为16进制0x12保存在convertedStr；
*/
int convert(const char* str, char* convertedStr)
{
	char tempStr[100];
	int result = 0;
	if (str[0] == '0') {
		int len = 0;
		while (str[len] != '\0') ++len;
		len -= 2;
		for (int i = 2; str[i] != '\0'; ++i) {
			int tempInt = str[i] - '0';
			int exp = 1;
			for (int j = 1; j < len; ++j) exp *= 16;
			result += exp * tempInt;
			--len;
		}
		//cout << result << endl;
		int i = 0;
		while (result) {
			tempStr[i++] = result % 10 + '0';
			result /= 10;
		}
		tempStr[i] = '\0';
		/*cout << tempStr << endl;
		cout << i << endl;*/
		for (int j = 0, k = i - 1; j < i / 2; ++j, --k)
			swapChar(tempStr[j], tempStr[k]);
		//cout << tempStr << endl;
		char* temp = tempStr;
		while (*convertedStr++ = *temp++); //不用strcpy
		//myStrcpy(convertedStr, tempStr);
		//cout << convertedStr << endl;
		return 0;
	}

	else {
		tempStr[0] = '0';
		tempStr[1] = 'x';
		int len = 0;
		int result = 0;
		while (str[len] != '\0') ++len;
		for (int i = 0; str[i] != '\0'; ++i) {
			int tempInt = str[i] - '0';
			int exp = 1;
			for (int j = 1; j < len; ++j) exp *= 10;
			result += exp * tempInt;
			--len;
		}

		int i = 2;

		while (result) {
			tempStr[i++] = decToHex(result % 16);
			result /= 16;
		}
		tempStr[i] = '\0';
		for (int j = 2, k = i - 1; j < (i - 2) / 2 + 2; ++j, --k)
			swapChar(tempStr[j], tempStr[k]);
		char* temp = tempStr;
		while (*convertedStr++ = *temp++); //不用strcpy
		//myStrcpy(convertedStr, tempStr);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	char str[] = "0x12345";
	char str1[] = "466069";
	char resultStr[100];
	convert(str, resultStr);
	cout << resultStr << endl;
	convert(str1, resultStr);
	cout << resultStr << endl;
	return 0;
}