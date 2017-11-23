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
选择排序算法：
第一个依次和后面比较，使得第一个为最小值
第二个类似，为第二小
****************************************/
void selectSort(SqList *L)
{
	for (int i = 0; i < L->length - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < L->length; ++j) {
			if (L->arr[j] < L->arr[minIndex])
				minIndex = j;
			//如果此处本来为最小值，那也不用交换了
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
