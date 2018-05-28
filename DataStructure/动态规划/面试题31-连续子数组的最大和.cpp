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








#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n;
	scanf("%d", &n);
	int sum = 0, mx = -99999999;    // 初值的选取需注意, 不能取INT_MIN
	for (int j = 0; j < n; j++){
		int temp;
		scanf("%d", &temp);
		if (sum < 0) sum = temp;
		else sum += temp;
		mx = max(sum, mx);
	}
	printf("%d\n", mx);
}
























#include <iostream>
#include <limits>

using namespace::std;

int findGreatestSumOfSubArray(int *arr, int length)
{
	int maxSum = 0, thisSum = 0;
	int i = length - 1;
	if (0 == i || findGreatestSumOfSubArray(arr, i) <= 0)
		return arr[i];
	else
		return arr[i] + findGreatestSumOfSubArray(arr, i - 1);
}

int findGreatestSumOfSubArray2(int *arr, int length)
{
	if (nullptr == arr || length <= 0)
		return 0;
	int maxSum = INT_MIN, thisSum = 0;
	for (int i = 0; i < length; ++i) {
		if (thisSum <= 0)
			thisSum = arr[i];
		else
			thisSum += arr[i];
		if (maxSum < thisSum)
			maxSum = thisSum;
	}

	return maxSum;
}

int findGreatestSumOfSubArrayWrong(int *arr, int length)
{
	if (nullptr == arr || length <= 0)
		return 0;
	int maxSum = INT_MIN, thisSum = 0;
	for (int i = 0; i < length; ++i) {
		thisSum += arr[i];
		if (thisSum <= 0)
			thisSum = 0;
		if (maxSum < thisSum)
			maxSum = thisSum;
	}

	return maxSum;
}

int main()
{
	int arr[] = { -2, 1, -2, 1, 2 };
	int length = sizeof(arr) / sizeof(arr[0]);
	cout << findGreatestSumOfSubArray2(arr, length) << endl;
	cout << findGreatestSumOfSubArrayWrong(arr, length) << endl;
}