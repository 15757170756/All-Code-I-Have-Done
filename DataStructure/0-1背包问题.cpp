#include <iostream>

using namespace::std;

// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
	int** K = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i)
		K[i] = new int[W + 1];

	for (int i = 0; i <= n; ++i) {
		for (int w = 0; w <= W; ++w) {
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = max(K[i - 1][w - wt[i - 1]] + val[i - 1],
				K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}

	return K[n][W];
}

int main()
{
	int val[] = { 60, 100, 120 };
	int wt[] = { 10, 20, 30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);
	cout << knapSack(W, wt, val, n) << endl;

	return 0;
}

/*
假设山洞里共有a,b,c,d ,e这5件宝物（不是5种宝物），
它们的重量分别是2,2,6,5,4，它们的价值分别是6,3,5,4,6，
现在给你个承重为10的背包, 怎么装背包，可以才能带走最多的财富。

有编号分别为a,b,c,d,e的五件物品，它们的重量分别是2,2,6,5,4，
它们的价值分别是6,3,5,4,6，现在给你个承重为10的背包，
如何让背包里装入的物品具有最大的价值总和？

name weight	value	1	2	3	4	5	6	7	8	9	10
a	2	    6	0	6	6	9	9	12	12	15	15	15
b	2	    3	0	3	3	6	6	9	9	9	10	11
c	6	    5	0	0	0	6	6	6	6	6	10	11
d	5	    4	0	0	0	6	6	6	6	6	10	10
e	4	    6	0	0	0	6	6	6	6	6	6	6

只要你能通过找规律手工填写出上面这张表就算理解了01背包的动态规划算法。

首先要明确这张表是至底向上，从左到右生成的。

为了叙述方便，用e2单元格表示e行2列的单元格，
这个单元格的意义是用来表示只有物品e时，有个承重为2的背包，
那么这个背包的最大价值是0，因为e物品的重量是4，背包装不了。

对于d2单元格，表示只有物品e，d时,承重为2的背包,所能装入的最大价值，
仍然是0，因为物品e,d都不是这个背包能装的。

同理，c2=0，b2=3,a2=6。

对于承重为8的背包，a8=15,是怎么得出的呢？

根据01背包的状态转换方程，需要考察两个值，

一个是f[i-1,j],对于这个例子来说就是b8的值9，另一个是f[i-1,j-Wi]+Pi；

在这里，

f[i-1,j]表示我有一个承重为8的背包，当只有物品b,c,d,e四件可选时，
这个背包能装入的最大价值

f[i-1,j-Wi]表示我有一个承重为6的背包（等于当前背包承重减去物品a的重量），
当只有物品b,c,d,e四件可选时，这个背包能装入的最大价值

f[i-1,j-Wi]就是指单元格b6,值为9，Pi指的是a物品的价值，即6

由于f[i-1,j-Wi]+Pi = 9 + 6 = 15 大于f[i-1,j] = 9，
所以物品a应该放入承重为8的背包

以下是actionscript3 的代码
*/