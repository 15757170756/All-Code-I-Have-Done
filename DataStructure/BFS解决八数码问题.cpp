/*
https://www.cnblogs.com/ABC-00/p/6022200.html
*/

#include<stdio.h>

struct node
{
	int xy[3][3];
	int dir;
};
struct node sh[102], end;
int count = 1;

void init()
{
	printf("输入起始节点的位置:\n");
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scanf("%d", &sh[0].xy[i][j]);
	sh[0].dir = -1;
	printf("输入目标节点的位置:\n");
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scanf("%d", &sh[101].xy[i][j]);
	sh[101].dir = -1;
}

//找出0的位置
int loction(int num)
{
	int i;
	for (i = 0; i < 9; i++)
		if (sh[num].xy[i / 3][i % 3] == 0) return i;
}


//进行标记
long long sign(int num)
{
	long long  sum;
	sum = sh[num].xy[0][0] * 100000000
		+ sh[num].xy[0][1] * 10000000
		+ sh[num].xy[0][2] * 1000000
		+ sh[num].xy[1][0] * 100000
		+ sh[num].xy[1][1] * 10000
		+ sh[num].xy[1][2] * 1000
		+ sh[num].xy[2][0] * 100
		+ sh[num].xy[2][1] * 10
		+ sh[num].xy[2][2];
	return sum;
}

void mobile(int num)
{

	int temp;
	int loc;
	int up = 1, down = 1, left = 1, right = 1;
	loc = loction(num);
	int stand = sh[num].dir;
	//dir的0 1 2 3分别代表左 上 右 下
	if (loc / 3 != 0 && stand != 1)
	{
		sh[count] = sh[num];
		temp = sh[count].xy[loc / 3][loc % 3];
		sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3 - 1][loc % 3];
		sh[count].xy[loc / 3 - 1][loc % 3] = temp;
		sh[count].dir = 3;
		count++;
	};
	if (loc / 3 != 2 && stand != 3)
	{
		sh[count] = sh[num];
		temp = sh[count].xy[loc / 3][loc % 3];
		sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3 + 1][loc % 3];
		sh[count].xy[loc / 3 + 1][loc % 3] = temp;
		sh[count].dir = 1;
		count++;
	}
	if (loc % 3 != 0 && stand != 0)
	{
		sh[count] = sh[num];
		temp = sh[count].xy[loc / 3][loc % 3];
		sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3][loc % 3 - 1];
		sh[count].xy[loc / 3][loc % 3 - 1] = temp;
		sh[count].dir = 2;
		count++;
	}
	if (loc % 3 != 2 && stand != 2)
	{
		sh[count] = sh[num];
		temp = sh[count].xy[loc / 3][loc % 3];
		sh[count].xy[loc / 3][loc % 3] = sh[count].xy[loc / 3][loc % 3 + 1];
		sh[count].xy[loc / 3][loc % 3 + 1] = temp;
		sh[count].dir = 0;
		count++;
	}

}
void display(int num)
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			printf("%d ", sh[num].xy[i][j]);
		printf("\n");
	}
}

int search()
{
	int i = 0;
	while (1)
	{
		printf("step %d:\n", i);
		display(i);
		printf("\n");
		if (i == 100)
		{
			printf("超出了上限次数\n");
			return 0;
		}
		if (sign(i) == sign(101))
		{
			printf("在第%d次找到了\n", i);
			display(i);
			return i;
		}
		mobile(i);
		i++;
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	init();
	search();
	return 0;
}
//测试用例
/*
2 8 3
1 6 4
7 0 5
1 2 3
7 8 4
0 6 5
*/