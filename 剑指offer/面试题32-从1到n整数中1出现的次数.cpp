#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <sstream>
#include <cmath>

using namespace::std;

int numberOf1(const char *strN)
{
	if (!strN || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;
	int first = *strN - '0';
	size_t length = strlen(strN);
	if (length == 1 && first == 0)
		return 0;
	if (length == 1 && first > 0)
		return 1;

	int numFirstDigit = 0;
	if (first > 1)
		numFirstDigit = pow(10, length - 1);
	else if (first == 1)
		numFirstDigit = atoi(strN + 1) + 1;

	int numOtherDigits = first * (length - 1) * pow(10, length - 2);
	int numRecursive = numberOf1(strN + 1);

	return numFirstDigit + numOtherDigits + numRecursive;
}

int numberOf1Between1Andn(int n)
{
	if (n <= 0)
		return 0;
	char strN[50];
	sprintf(strN, "%d", n);
	return numberOf1(strN);
}

int main(int argc, char* argv[])
{
	int a = 31345;
	cout << numberOf1Between1Andn(a) << endl;
	cout << numberOf1Between1Andn(a) - numberOf1Between1Andn(21346) << endl;

	return 0;
}





