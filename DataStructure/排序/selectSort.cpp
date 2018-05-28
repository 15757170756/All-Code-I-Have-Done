#include <stdio.h>

#define arrLength 10

typedef struct {
	int arr[arrLength];
	int length;
}SqList;

void swap(SqList *L, int i, int j)
{
	int temp = L->arr[i];
	L->arr[i] = L->arr[j];
	L->arr[j] = temp;
}

/***************************************
ѡ�������㷨��
��һ�����κͺ���Ƚϣ�ʹ�õ�һ��Ϊ��Сֵ
�ڶ������ƣ�Ϊ�ڶ�С
****************************************/
void selectSort(SqList *L)
{
	for (int i = 0; i < L->length - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < L->length; ++j) {
			if (L->arr[j] < L->arr[minIndex])
				minIndex = j;
			//����˴�����Ϊ��Сֵ����Ҳ���ý�����
			if (minIndex != i)
				swap(L, i, minIndex);
		}
	}
}

int main()
{
	SqList L{ { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 }, 10 };
	//bubbleSort0(&L);
	//for (int i = 0; i < L.length; ++i)
	//	printf("%d ", L.arr[i]);

	//bubbleSort1(&L);
	//for (int i = 0; i < L.length; ++i)
	//	printf("%d ", L.arr[i]);

	selectSort(&L);
	for (int i = 0; i < L.length; ++i)
		printf("%d ", L.arr[i]);
	return 0;
}

















// C program for implementation of selection sort
#include <stdio.h>

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// Driver program to test above functions
int main()
{
	int arr[] = { 64, 25, 12, 22, 11 };
	int n = sizeof(arr) / sizeof(arr[0]);
	selectionSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	return 0;
}