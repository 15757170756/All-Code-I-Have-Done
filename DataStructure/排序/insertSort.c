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
插入排序算法：（基于移动实现）
是假定一个数组是排序好的，从数组的第二个
元素开始，因为第一个元素认为就是有序的，
第一个循环i控制的是第i个元素要插入到前面
已经有序的数组中去；第二个for循环j是从大
到小递减的，即将第i-1及之前的元素移位
好让第i个元素插入。
****************************************/
void insertSort1(SqList *L)
{
	for (int i = 1, j; i < L->length; ++i) {
		int key = L->arr[i];
		for (j = i - 1; j >= 0 && L->arr[j] > key; --j)
			L->arr[j + 1] = L->arr[j];
		L->arr[j + 1] = key;
	}
}

/***************************************
插入排序算法：（基于交换实现）
是假定一个数组是排序好的，从数组的第二个
元素开始，因为第一个元素认为就是有序的，
第一个循环i控制的是第i个元素要插入到前面
已经有序的数组中去；第二个for循环j是从大
到小递减的，即将第i-1及之前的元素移位
好让第i个元素插入。
****************************************/
void insertSort2(SqList *L)
{
	for (int i = 1, j; i < L->length; ++i) {
		for (j = i - 1; j >= 0 && L->arr[j] > L->arr[j + 1]; --j)
			swap(L, j, j + 1);
	}
}


int main()
{
	SqList L{ { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 }, 10 };

	//insertSort1(&L);
	//for (int i = 0; i < L.length; ++i)
	//	printf("%d ", L.arr[i]);

	insertSort1(&L);
	for (int i = 0; i < L.length; ++i)
		printf("%d ", L.arr[i]);

	return 0;
}
