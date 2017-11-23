#include <iostream>

using namespace::std;

//online Process
int findGreatestSumofSubArray(int arr[], int arrLength)
{
	if (arr == nullptr || arrLength < 1)
		return 0;
	int currSum = 0;
	int greatestSum = 0x80000000;
	for (int i = 0; i < arrLength; ++i) {
		if (currSum <= 0)
			currSum = arr[i];
		else
			currSum += arr[i];
		if (currSum > greatestSum)
			greatestSum = currSum;
	}
	return greatestSum;
}

//traverse
int findGreatestSumofSubArray2(int arr[], int arrLength)
{
	if (arr == nullptr || arrLength < 1)
		return 0;
	int currSum = 0;
	int greatestSum = 0x80000000;
	for (int i = 0; i < arrLength; ++i) {
		currSum = 0;
		for (int j = i; j < arrLength; ++j) {
			currSum += arr[j];
			if (currSum > greatestSum)
				greatestSum = currSum;
		}
	}
	return greatestSum;
}



int main()
{
	int arr[] = { 1, 2, 3, 10, -4, 7, 2, 5 };
	int arrLength = sizeof(arr) / sizeof(int);
	int maxSubArray = findGreatestSumofSubArray(arr, arrLength);
	cout << maxSubArray << endl;

	return 0;
}