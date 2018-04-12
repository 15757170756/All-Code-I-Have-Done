#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iterator>

using namespace::std;

bool findNumbersWithSum(int *data, int length, int sum,
	int *num1, int *num2)
{
	bool found = false;
	if (length < 1 || num1 == nullptr || num2 == nullptr)
		return found;

	int end = length - 1;
	int start = 0;

	while (end > start) {
		int curSum = data[start] + data[end];
		if (curSum == sum) {
			*num1 = data[start];
			*num2 = data[end];
			found = true;
			break;
		}
		else if (curSum > sum)
			--end;
		else
			++start;
	}

	return found;
}

int main(int argc, char* argv[])
{
	int arr[] = { 1, 2, 4, 7, 11, 15 };
	int num1, num2, sum = 15;
	int length = sizeof(arr) / sizeof(arr[0]);
	bool found = findNumbersWithSum(arr, length, sum, &num1, &num2);
	if (found) {
		cout << num1 << ' ' << num2 << endl;
	}

	return 0;
}


