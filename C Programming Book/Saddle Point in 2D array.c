/***************************************
Ѱ�Ҷ�ά����İ��㣺����λ���ϵ�Ԫ���ڸ������
�ڸ�����С��Ҳ����û�а��㡣
****************************************/

#include <stdio.h>

#define M 3
#define N 4

int main()
{
	//�а���
	//int a[M][N] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
	//int a[M][N] = { { 2, 5, 3 }, { 3, 4, 2 } };
	//int a[M][N] = { { 8, 11, 9 }, { 10, 10, 9 }, { 8, 9, 3 } };
	//�ް���
	int a[M][N] = { { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 } };
	int saddlePointNum = findSaddlepoint(a);
	if (saddlePointNum == 0)
		printf("û�а���\n");
	else
		printf("�����ǣ�%d\n", saddlePointNum);

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
		if (k == M - 1 && rowMax != a[k][j]) //���û�к������rowMax != a[k][j],ȫ����1����Ϊ1Ҳ�ǰ��㣬����Ӧ�ò���
			return rowMax;
	}

	return 0;
}