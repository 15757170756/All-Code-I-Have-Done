#include <iostream>
#include <algorithm>

using namespace::std;

//int compare(const void *arg1, const void *arg2)
//{
//	return *(int*)arg1 - *(int*)arg2;
//}

bool compare(const int arg1, const int arg2)
{
	return arg1 < arg2;
}

bool isContinuous(int *numbers, int length)
{
	if (numbers == nullptr || length < 1)
		return false;

	//qsort(numbers, length, sizeof(int), compare);
	sort(numbers, numbers + length, compare);
	int numberOfZeros = 0;
	int numberOfGap = 0;

	for (int i = 0; i < length && numbers[i] == 0; ++i)
		++numberOfZeros;
	int small = numberOfZeros;
	int big = small + 1;
	while (big < length) {
		if (numbers[small] == numbers[big])
			return false;
		numberOfGap += numbers[big] - numbers[small] - 1;
		small = big;
		++big;
	}
	return (numberOfGap > numberOfZeros ? false : true);
}

int main(int argc, char* argv[])
{
	int arr[] = { 8, 9, 10, 11, 0, 5 };
	int length = sizeof(arr) / sizeof(arr[0]);

	cout << boolalpha << isContinuous(arr, length) << noboolalpha << endl;

	return 0;
}




