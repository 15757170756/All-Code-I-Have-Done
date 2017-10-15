/***************************************
二分法查找已排序中的元素
****************************************/

#include <stdio.h>

int binarySearch(int a[], int n, int key);

int main()
{
	int a[4] = { 1, 2, 3, 4 };
	int key = 0;
	int result = binarySearch(a, 4, key);
	if (result == 1)
		printf("find the element: %d\n", key);
	else
		printf("don't find the element\n");
}

int binarySearch(int a[], int n, int key)
{
	int start = 0, end = n - 1;
	int middle;
	while (start <= end) {
		middle = (start + end) / 2;
		if (a[middle] == key)
			return 1;
		else if (a[middle] > key)
			end = middle - 1;
		else
			start = middle + 1;
	}
	if (start > end)
		return 0;
}