#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iterator>

using namespace::std;

int getFirstK(int* data, int length, int k, int start, int end)
{
	if (start > end)
		return -1;
	int midIndex = (start + end) / 2;
	int midData = data[midIndex];

	if (midData == k) {
		if ((midIndex > 0 && data[midIndex - 1] != k)
			|| midIndex == 0)
			return midIndex;
		else
			end = midIndex - 1;
	}
	else if (midData > k)
		end = midIndex - 1;
	else
		start = midIndex + 1;

	return getFirstK(data, length, k, start, end);
}

int getLastK(int* data, int length, int k, int start, int end)
{
	if (start > end)
		return -1;
	int midIndex = (start + end) / 2;
	int midData = data[midIndex];

	if (midData == k) {
		if ((midIndex < length - 1 && data[midIndex + 1] != k)
			|| midIndex == length - 1)
			return midIndex;
		else
			start = midIndex + 1;
	}
	else if (midData > k)
		end = midIndex - 1;
	else
		start = midIndex + 1;

	return getLastK(data, length, k, start, end);
}

int getNumberOfK(int *data, int length, int k)
{
	int number = 0;
	if (data != nullptr && length > 0) {
		int firstKIndex = getFirstK(data, length, k, 0, length - 1);
		int lastKIndex = getLastK(data, length, k, 0, length - 1);
		if (firstKIndex > -1 && lastKIndex > -1)
			number = lastKIndex - firstKIndex + 1;
	}

	return number;
}

int main(int argc, char* argv[])
{
	int arr[] = { 3, 3, 3, 3, 3, 3, 4, 5 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int k = 3;
	cout << getNumberOfK(arr, length, k) << endl;
	return 0;
}


