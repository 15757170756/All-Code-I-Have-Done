#include <iostream>
#include <list>
#include <algorithm>

using namespace::std;

int add(int num1, int num2)
{
	int sum, carry;
	do {
		sum = num1 ^ num2;
		carry = (num1 & num2) << 1;

		num1 = sum;
		num2 = carry;
	} while (num2 != 0);

	return num1;
}

int main(int argc, char* argv[])
{
	int a = 5, b = 9;
	cout << add(a, b) << endl;

	return 0;
}




