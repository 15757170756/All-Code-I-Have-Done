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
ð�ư�ð���㷨��
ֻ��˳���L����������ð����������棩
��һ���͵ڶ�����������һ�αȽϣ����С��
ʹ�õ�һ��Ϊ��С��
****************************************/
void bubbleSort0(SqList *L)
{
	for (int i = 0; i < L->length - 1; ++i)
		for (int j = i + 1; j < L->length; ++j)
			if (L->arr[i] > L->arr[j])
				swap(L, i, j);
}

/***************************************
��ȷ��ð���㷨��
�Ƚ���������Ԫ�أ�һ����˵��һ��forѭ��
�ǿ����ܵĴ�����һ���0��n-1�����ڶ���
forѭ���Ϳ�������ô��ð���ˣ���С��ð��
���滹�Ǵ�ĳ������£������С��ð������
һ��j��Ҫ��n-1��i�ģ�����ǳ������£���
j��0��n-1-i��
****************************************/
void bubbleSort1(SqList *L)
{
	//С��ð������
	//for (int i = 0; i < L->length - 1; ++i)
	//	for (int j = L->length - 1; j > i; --j)
	//		if (L->arr[j] < L->arr[j - 1])
	//			swap(L, j, j - 1);

	//��ĳ�������
	for (int i = 0; i < L->length - 1; ++i)
		for (int j = 0; j < L->length - 1 - i; ++j)
			if (L->arr[j] > L->arr[j + 1])
				swap(L, j, j + 1);

}

/***************************************
�Ľ���ð���㷨��
���flag�����жϵڶ���forѭ�����Ƿ��Ѿ�
���ź���ģ������÷�������������������ˣ�
˵��δ�ź��������ڽ���������flag��ֵ
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







