#include <iostream>

using namespace::std;

int Min(int* numbers, int length);
int MinInorder(int* numbers, int index1, int index2);

int main()
{
	int arr[] = { 3.4, 4, 1, 2, 2 };
	int arrLength = sizeof(arr) / sizeof(int);
	int result = Min(arr, arrLength);
	cout << result << endl;

	return 0;
}

int Min(int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		return 0;

	int index1 = 0, index2 = length - 1;
	int indexMid = index1;
	while (numbers[index1] >= numbers[index2]) {
		if (index2 - index1 == 1) {
			indexMid = index2;
			break;
		}

		indexMid = (index1 + index2) / 2;

		if (numbers[indexMid] == numbers[index1] &&
			numbers[index1] == numbers[index2])
			return MinInorder(numbers, index1, index2);

		if (numbers[index1] <= numbers[indexMid])
			index1 = indexMid;
		else if (numbers[index2] >= numbers[indexMid])
			index2 = indexMid;
	}

	return numbers[indexMid];
}

int MinInorder(int* numbers, int index1, int index2)
{
	int result = numbers[index1];
	for (int i = index1 + 1; i <= index2; ++i)
		if (result > numbers[i])
			result = numbers[i];

	return result;
}