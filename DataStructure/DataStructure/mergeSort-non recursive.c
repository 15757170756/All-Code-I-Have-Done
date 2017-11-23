/***************************************
Iterative Merge Sort:
The above function is recursive, 
so uses function call stack to store
intermediate values of l and h. 
The function call stack stores other 
bookkeeping information together 
with parameters. Also, function calls involve 
overheads like storing activation record of the 
caller function and then resuming execution. 
Unlike Iterative QuickSort, the iterative 
MergeSort doesn¡¯t require explicit auxiliary stack.
The above function can be easily converted to 
iterative version. Following is iterative Merge Sort.
****************************************/



#include <stdio.h>
#include <stdlib.h>

void mergeSort(int arr[], int n);
void merge(int arr[], int start, int mid, int end);
int minimum(int x, int y) { return (x < y) ? x : y; }

int main()
{
	int a[] = { 4, 3, 5, 2, 1, -2, 9, 7 };
	int arrLength = sizeof(a) / sizeof(int);
	mergeSort(a, arrLength);
	for (int i = 0; i < arrLength; ++i)
		printf("%d ", a[i]);

	return 0;
}

/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int arr[], int n)
{
	int currSize;  // For current size of subarrays to be merged
	// curr_size varies from 1 to n/2
	int leftStart; // For picking starting index of left subarray
	// to be merged

	// Merge subarrays in bottom up manner.  First merge subarrays of
	// size 1 to create sorted subarrays of size 2, then merge subarrays
	// of size 2 to create sorted subarrays of size 4, and so on.
	for (currSize = 1; currSize <= n - 1; currSize = 2 * currSize) {
		// Pick starting point of different subarrays of current size
		for (leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
			// Find ending point of left subarray. mid+1 is starting 
			// point of right
			int mid = leftStart + currSize - 1;

			int rightEnd = minimum(mid + currSize, n - 1);

			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			merge(arr, leftStart, mid, rightEnd);
		}
	}
}

void merge(int arr[], int start, int mid, int end)
{
	int leftNum = mid - start + 1;
	int rightNum = end - mid;

	/* create temp arrays */
	int* leftArr = (int*)malloc(leftNum*sizeof(int));
	int* rightArr = (int*)malloc(rightNum*sizeof(int));

	/* Copy data to temp arrays L[] and R[] */
	for (int i = 0; i < leftNum; ++i)
		leftArr[i] = arr[start + i];
	for (int i = 0; i < rightNum; ++i)
		rightArr[i] = arr[mid + 1 + i];

	/* Merge the temp arrays back into arr[l..r]*/
	int k = start;
	int i = 0, j = 0;
	while (i < leftNum && j < rightNum) {
		if (leftArr[i] < rightArr[j])
			arr[k++] = leftArr[i++];
		else
			arr[k++] = rightArr[j++];
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < leftNum)
		arr[k++] = leftArr[i++];

	/* Copy the remaining elements of R[], if there are any */
	while (j < rightNum)
		arr[k++] = rightArr[j++];

	free(leftArr);
	free(rightArr);
}