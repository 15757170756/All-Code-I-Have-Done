/***************************************
寻找二维数组的鞍点：即该位置上的元素在该行最大，
在该列最小。也可能没有鞍点。
****************************************/

#include <stdio.h>

#define M 3
#define N 4

int main()
{
	//有鞍点
	//int a[M][N] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
	//int a[M][N] = { { 2, 5, 3 }, { 3, 4, 2 } };
	//int a[M][N] = { { 8, 11, 9 }, { 10, 10, 9 }, { 8, 9, 3 } };
	//无鞍点
	int a[M][N] = { { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 } };
	int saddlePointNum = findSaddlepoint(a);
	if (saddlePointNum == 0)
		printf("没有鞍点\n");
	else
		printf("鞍点是：%d\n", saddlePointNum);

	return 0;
}

int findSaddlepoint(int (*a)[N])
{
	int i, j, k, rowMax;
	for (i = 0; i < M; ++i) {
		rowMax = a[i][0];
		for (j = 0; j < N; ++j) {
			if (a[i][j] > rowMax)
				rowMax = a[i][j];
		}
		--j;
		for (k = i; k < M - 1; ++k) {
			if (rowMax >= a[k + 1][j])
				break;
		}
		if (k == M - 1 && rowMax != a[k][j]) //如果没有后面这个rowMax != a[k][j],全部是1，认为1也是鞍点，但是应该不是
			return rowMax;
	}

	return 0;
}