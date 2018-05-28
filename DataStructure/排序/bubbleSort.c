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
冒牌版冒泡算法：
只对顺序表L作交换排序（冒泡排序初级版）
第一个和第二个、第三个一次比较，如果小，
使得第一个为最小。
****************************************/
void bubbleSort0(SqList *L)
{
	for (int i = 0; i < L->length - 1; ++i)
		for (int j = i + 1; j < L->length; ++j)
			if (L->arr[i] > L->arr[j])
				swap(L, i, j);
}

/***************************************
正确版冒泡算法：
比较相邻两个元素，一般来说第一个for循环
是控制总的次数，一般从0到n-1，而第二个
for循环就看是想怎么“冒”了：是小的冒到
上面还是大的沉到底下，如果是小的冒到上面
一般j是要从n-1到i的；如果是沉到底下，则
j从0到n-1-i；
****************************************/
void bubbleSort1(SqList *L)
{
	//小的冒到上面
	//for (int i = 0; i < L->length - 1; ++i)
	//	for (int j = L->length - 1; j > i; --j)
	//		if (L->arr[j] < L->arr[j - 1])
	//			swap(L, j, j - 1);

	//大的沉到下面
	for (int i = 0; i < L->length - 1; ++i)
		for (int j = 0; j < L->length - 1 - i; ++j)
			if (L->arr[j] > L->arr[j + 1])
				swap(L, j, j + 1);

}

/***************************************
改进版冒泡算法：
添加flag用于判断第二个for循环中是否已经
是排好序的（即不用发生交换），如果交换了，
说明未排好序，所以在交换处更改flag的值
****************************************/
void bubbleSort2(SqList *L)
{
	int flag = 1;
	for (int i = 0; i < L->length - 1 && flag; ++i) {
		flag = 0;
		for (int j = 0; j < L->length - 1 - i; ++j)
			if (L->arr[j] > L->arr[j + 1]) {
				swap(L, j, j + 1);
				flag = 1;
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

	bubbleSort2(&L);
	for (int i = 0; i < L.length; ++i)
		printf("%d ", L.arr[i]);
	return 0;
}








#include <iostream>
#include <algorithm>

using namespace::std;

void bubbleSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < n - 1 - i; ++j)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}

int main(int argc, char* argv[])
{
	int arr[] = { 5, 4, 6, 7, 8, -3, 0 };
	int length = sizeof(arr) / sizeof(arr[0]);
	cout << "before sort:\n";
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
	cout << "after sort:\n";
	bubbleSort(arr, length);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;

	return 0;
}







