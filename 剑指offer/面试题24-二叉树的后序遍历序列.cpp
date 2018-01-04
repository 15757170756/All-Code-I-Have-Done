#include <iostream>

using namespace::std;

bool isSquenceOfBST(int sequence[], int arrLength)
{
	if (!sequence || arrLength <= 0)
		return false;

	int root = sequence[arrLength - 1];

	int i = 0;
	for (; i < arrLength - 1; ++i)
		if (sequence[i] > root)
			break;

	int j = i;
	for (; j < arrLength - 1; ++j)
		if (sequence[j] < root)
			return false;

	bool left = true;
	if (i > 0)
		left = isSquenceOfBST(sequence, i);

	bool right = true;
	if (i < arrLength - 1)
		right = isSquenceOfBST(sequence + i, arrLength - 1 - i);

	return (left && right);
}

int main()
{
	int arr1[] = { 5, 7, 6, 11, 10, 8 };
	int arr1Lenght = sizeof(arr1) / sizeof(arr1[0]);
	cout << boolalpha << isSquenceOfBST(arr1, arr1Lenght) << endl;

	int arr2[] = { 7, 4, 6, 5 };
	int arr2Lenght = sizeof(arr2) / sizeof(arr2[0]);
	cout << boolalpha << isSquenceOfBST(arr2, arr2Lenght) << endl;

	return 0;
}