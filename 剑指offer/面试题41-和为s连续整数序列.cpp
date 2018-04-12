#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;

void printSequence(int small, int big)
{
	for (int i = small; i <= big; ++i)
		cout << i << ' ';
	cout << endl;
}

void findContinuousSequence(int sum)
{
	if (sum < 3)
		return;
	int small = 1, big = 2;
	int curSum = small + big;
	int mid = (1 + sum) / 2;
	while (small < mid) {
		if (curSum == sum)
			printSequence(small, big);
		while (curSum > sum && small < mid) {
			curSum -= small;
			++small;
			if (curSum == sum)
				printSequence(small, big);
		}
		++big;
		curSum += big;
	}
}

int main(int argc, char* argv[])
{
	int sum = 30;
	findContinuousSequence(sum);

	return 0;
}




