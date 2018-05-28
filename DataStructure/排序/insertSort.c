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
���������㷨���������ƶ�ʵ�֣�
�Ǽٶ�һ������������õģ�������ĵڶ���
Ԫ�ؿ�ʼ����Ϊ��һ��Ԫ����Ϊ��������ģ�
��һ��ѭ��i���Ƶ��ǵ�i��Ԫ��Ҫ���뵽ǰ��
�Ѿ������������ȥ���ڶ���forѭ��j�ǴӴ�
��С�ݼ��ģ�������i-1��֮ǰ��Ԫ����λ
���õ�i��Ԫ�ز��롣
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
���������㷨�������ڽ���ʵ�֣�
�Ǽٶ�һ������������õģ�������ĵڶ���
Ԫ�ؿ�ʼ����Ϊ��һ��Ԫ����Ϊ��������ģ�
��һ��ѭ��i���Ƶ��ǵ�i��Ԫ��Ҫ���뵽ǰ��
�Ѿ������������ȥ���ڶ���forѭ��j�ǴӴ�
��С�ݼ��ģ�������i-1��֮ǰ��Ԫ����λ
���õ�i��Ԫ�ز��롣
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
