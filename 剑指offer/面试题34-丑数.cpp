#include <iostream>
#include <algorithm>

using namespace::std;

int getUglyNumber(int index)
{
	if (index <= 0)
		return 0;
	int *uglyNumbers = new int[index];
	uglyNumbers[0] = 1;
	int nextUglyIndex = 1;

	int *T2 = uglyNumbers;
	int *T3 = uglyNumbers;
	int *T5 = uglyNumbers;

	while (nextUglyIndex < index) {
		int minNum = min(min(*T2 * 2, *T3 * 3), *T5 * 5);
		uglyNumbers[nextUglyIndex] = minNum;
		while (*T2 * 2 <= uglyNumbers[nextUglyIndex])
			++T2;
		while (*T3 * 3 <= uglyNumbers[nextUglyIndex])
			++T3;
		while (*T5 * 5 <= uglyNumbers[nextUglyIndex])
			++T5;

		++nextUglyIndex;
	}

	int ugly = uglyNumbers[nextUglyIndex - 1];
	delete[] uglyNumbers;
	return ugly;
}

int main()
{
	int index = 1500;
	cout << getUglyNumber(index) << endl;
	for (int i = 1; i <= 20; ++i)
		cout << getUglyNumber(i) << endl;

	return 0;
}