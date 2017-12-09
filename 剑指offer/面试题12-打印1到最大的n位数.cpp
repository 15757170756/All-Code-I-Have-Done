#include <iostream>
#include <cstring>

using namespace::std;

/*
不考虑这个n位数超出
long long范围
*/
void print1Ton(unsigned int n)
{
	if (n <= 0)
		return;
	int maxNum = 1;
	while (n) {
		maxNum *= 10;
		--n;
	}

	maxNum -= 1;
	for (int i = 1; i <= maxNum; ++i);
	//cout << i << ' ';
	cout << maxNum;
	cout << endl;
}

bool Increment(char* strNum)
{
	bool isOverflow = false;
	int nTakeOver = 0;
	int strlength = strlen(strNum);
	for (int i = strlength - 1; i >= 0; --i) {
		int nSum = strNum[i] - '0' + nTakeOver;
		if (i == strlength - 1)
			nSum++;

		if (nSum >= 10) {
			if (i == 0)
				isOverflow = true;
			else {
				nSum -= 10;
				nTakeOver = 1;
				strNum[i] = '0' + nSum;
			}
		}
		else {
			strNum[i] = '0' + nSum;
			break;
		}
	}

	return isOverflow;
}

void printNumber(char* strNum)
{
	bool isBeginning0 = true;
	int strLength = strlen(strNum);

	for (int i = 0; i < strLength; ++i) {
		if (isBeginning0 && strNum[i] != '0')
			isBeginning0 = false;

		if (!isBeginning0)
			printf("%c", strNum[i]);
	}

	printf("\t");
}

/*
使用字符串来输出数字
*/
void print1TonStr(unsigned int n)
{
	if (n <= 0)
		return;

	char* strNum = new char[n + 1];
	memset(strNum, '0', n);
	strNum[n] = '\0';

	while (!Increment(strNum))
		printNumber(strNum);

	delete[] strNum;
}


void print1ToMaxOfNDigitsRecusively(char* number, unsigned int length, int index)
{
	if (index == length - 1) {
		printNumber(number);
		return;
	}

	for (int i = 0; i < 10; ++i) {
		number[index + 1] = i + '0';
		print1ToMaxOfNDigitsRecusively(number, length, index + 1);
	}
}

/*
全排列解法
*/
void print1ToMaxOfNDigits(unsigned int n)
{
	if (n <= 0)
		return;
	char* number = new char[n + 1];
	number[n] = '\0';

	for (int i = 0; i < 10; ++i) {
		number[0] = i + '0';
		print1ToMaxOfNDigitsRecusively(number, n, 0);
	}

	delete[] number;
}

int main()
{
	print1Ton(3);
	print1TonStr(3);
	print1ToMaxOfNDigits(3);

	return 0;
}