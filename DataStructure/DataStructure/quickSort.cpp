#include <stdio.h>
#include <cstdlib>

int partition_exchangeElem(int arr[], int low, int high);//交换元素
int partition_nonExchangeElem(int arr[], int low, int high);//不交换元素
void swap(int* a, int *b) { int temp = *a; *a = *b; *b = temp; }
void quickSort(int arr[], int low, int high);
void quickSortTailRecursion(int arr[], int low, int high);//尾递归
void printArray(int arr[], int size);

int main()
{
	int arr[] = { 10, 7, 8, 9, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSortTailRecursion(arr, 0, n - 1);
	printf("Sorted array: \n");
	printArray(arr, n);
	return 0;
}


int partition_exchangeElem(int arr[], int low, int high)
{
	int pivotkey = arr[low];
	while (low < high) {
		while (low < high && arr[high] >= pivotkey)
			--high;
		swap(&arr[high], &arr[low]);

		while (low < high && arr[low] <= pivotkey)
			++low;
		swap(&arr[low], &arr[high]);
	}

	return low;
}

int partition_nonExchangeElem(int arr[], int low, int high)
{
	int pivotkey = arr[low];
	while (low < high) {
		while (low < high && arr[high] >= pivotkey)
			--high;
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivotkey)
			++low;
		arr[high] = arr[low];
	}

	arr[low] = pivotkey;
	return low;
}

int randomizedPartition(int arr[], int low, int high)
{
	int randInteger = low + rand() % (high - low + 1);
	swap(&arr[randInteger], &arr[low]);
	int pivotkey = arr[low];
	while (low < high) {
		while (low < high && arr[high] >= pivotkey)
			--high;
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivotkey)
			++low;
		arr[high] = arr[low];
	}

	arr[low] = pivotkey;
	return low;
}

int Partition(int *arr, int length, int start, int end)
{
	if (nullptr == arr || length < 0
		|| start < 0 || end >= length)
		return 0;

	int index = start + rand() % (end - start + 1);
	swap(&arr[index], &arr[end]);

	int small = start - 1;

	for (index = start; index < end; ++index) {
		if (arr[index] < arr[end]) {
			++small;
			if (arr[small] != arr[index])
				swap(&arr[small], &arr[index]);
		}
	}

	++small;
	swap(&arr[small], &arr[end]);
	return small;
}

void quickSort(int arr[], int low, int high)
{
	if (low >= high)
		return;
	int pivotPos = partition_nonExchangeElem(arr, low, high);
	quickSort(arr, low, pivotPos - 1);
	quickSort(arr, pivotPos + 1, high);
}

void quickSortTailRecursion(int arr[], int low, int high)
{
	if (low >= high)
		return;
	int pivotPos;
	while (low < high) {
		pivotPos = partition_nonExchangeElem(arr, low, high);
		quickSortTailRecursion(arr, low, pivotPos - 1);
		low = pivotPos + 1;
	}

}

void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}