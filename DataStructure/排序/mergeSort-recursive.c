#include <stdio.h>
#include <stdlib.h>

void mergeSort(int arr[], int start, int end);
void merge(int arr[], int start, int mid, int end);

int main()
{
	int a[5] = { 4, 3, 5, 2, 1 };
	mergeSort(a, 0, 4);
	for (int i = 0; i < 5; ++i)
		printf("%d ", a[i]);

	return 0;
}

void mergeSort(int arr[], int start, int end)
{
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

void merge(int arr[], int start, int mid, int end)
{
	int leftNum = mid - start + 1;
	int rightNum = end - mid;

	int* leftArr = (int*)malloc(leftNum*sizeof(int));
	int* rightArr = (int*)malloc(rightNum*sizeof(int));

	for (int i = 0; i < leftNum; ++i)
		leftArr[i] = arr[start + i];
	for (int i = 0; i < rightNum; ++i)
		rightArr[i] = arr[mid + 1 + i];

	int k = start;
	int i = 0, j = 0;
	while (i < leftNum && j < rightNum) {
		if (leftArr[i] < rightArr[j])
			arr[k++] = leftArr[i++];
		else
			arr[k++] = rightArr[j++];
	}

	while (i < leftNum)
		arr[k++] = leftArr[i++];
	while (j < rightNum)
		arr[k++] = rightArr[j++];

	free(leftArr);
	free(rightArr);
}