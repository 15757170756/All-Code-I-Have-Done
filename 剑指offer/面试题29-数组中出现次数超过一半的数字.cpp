#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace::std;

bool g_bInputInvalid = false;

void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

int Partition(int data[], int length, int start, int end)
{
	if (nullptr == data || length < 0
		|| start < 0 || end >= length)
		throw new exception("Invalid Parameters");

	int index = start + rand() % (end - start + 1);
	swap(data[index], data[end]);

	int small = start - 1;
	for (index = start; index < end; ++index) {
		if (data[index] < data[end]) {
			++small;
			if (small != index)
				swap(data[index], data[small]);
		}
	}

	++small;
	swap(data[small], data[end]);

	return small;
}

bool CheckInvalidArray(int *numbers, int length)
{
	g_bInputInvalid = false;
	if (numbers == nullptr && length <= 0)
		g_bInputInvalid = true;

	return g_bInputInvalid;
}

bool CheckMoreThanHalf(int *numbers, int length, int number)
{
	int times = 0;
	for (int i = 0; i < length; ++i)
		if (numbers[i] == number)
			++times;

	bool isMoreThanHalf = true;
	if (times * 2 <= length) {
		g_bInputInvalid = true;
		isMoreThanHalf = false;
	}

	return isMoreThanHalf;
}

int MoreThanHalfNum(int *numbers, int length)
{
	if (CheckInvalidArray(numbers, length))
		return 0;

	int middle = length >> 1;
	int start = 0, end = length - 1;
	int index = Partition(numbers, length, start, end);
	while (index != middle) {
		if (index > middle) {
			end = index - 1;
			index = Partition(numbers, length, start, end);
		}
		else {
			start = index + 1;
			index = Partition(numbers, length, start, end);
		}
	}

	int result = numbers[middle];
	if (!CheckMoreThanHalf(numbers, length, result))
		return 0;

	return result;
}

int MoreThanHalfNum2(int *numbers, int length)
{
	if (CheckInvalidArray(numbers, length))
		return 0;

	int result = numbers[0];
	int times = 1;
	for (int i = 1; i < length; ++i) {
		if (0 == times) {
			result = numbers[i];
			times = 1;
		}
		else if (numbers[i] == result)
			++times;
		else
			--times;
	}
	if (!CheckMoreThanHalf(numbers, length, result))
		result = 0;

	return result;
}

int main()
{
	int arr[] = { 2, 2, 3, 2, 5, 2, 4, 2, 1 };
	int length = sizeof(arr) / sizeof(arr[0]);
	cout << MoreThanHalfNum2(arr, length) << endl;
	return 0;
}