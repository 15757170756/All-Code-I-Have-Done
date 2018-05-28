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
希尔排序算法（基于插入排序交换法）：
增量插入排序，其实已经有些分治法的意思在了
将数组分为n组，依据为增量的大小，每组使用
插入法排序。
****************************************/
void shellSort1(SqList *L)
{
	for (int increment = L->length / 2; increment > 0; increment /= 2) {
		for (int i = increment; i < L->length; ++i)
			for (int j = i; j - increment >= 0 && L->arr[j] < L->arr[j - increment]; j -= increment)
				swap(L, j, j - increment);
	}
}

/***************************************
希尔排序算法（基于插入排序移动法）：
增量插入排序，其实已经有些分治法的意思在了
将数组分为n组，依据为增量的大小，每组使用
插入法排序。
****************************************/
void shellSort2(SqList *L)
{
	for (int increment = L->length / 2; increment > 0; increment /= 2) {
		for (int i = increment; i < L->length; ++i) {
			int j = i;
			int key = L->arr[j];
			if (L->arr[j] < L->arr[j - increment]) {
				while (j - increment >= 0 && key < L->arr[j - increment]) {
					L->arr[j] = L->arr[j - increment];
					j -= increment;
				}
				L->arr[j] = key;
			}
		}
	}
}

int main()
{
	SqList L{ { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 }, 10 };

	shellSort2(&L);
	for (int i = 0; i < L.length; ++i)
		printf("%d ", L.arr[i]);

	return 0;
}