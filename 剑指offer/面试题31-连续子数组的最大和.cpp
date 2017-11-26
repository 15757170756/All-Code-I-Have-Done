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