/***************************************
题目描述

一个数组有N个元素，求连续子数组的最大和。例如：[-1,2,1]，和最大的连续子数组为[2,1]，其和为3。

输入描述

输入为两行。
第一行一个整数n (1 <= n <= 100000), 表示一共有n个元素，第二行为n个数，每个元素每个整数都在32位int范围内。以空格分隔。
输出描述

所有连续子数组中和最大的值。
输入例子

3
-1 2 1
输出例子

3
****************************************/


#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n;
	scanf("%d", &n);
	int sum = 0, mx = -99999999;    // 初值的选取需注意, 不能取INT_MIN
	for (int j = 0; j < n; j++){
		int temp;
		scanf("%d", &temp);
		if (sum < 0) sum = temp;
		else sum += temp;
		mx = max(sum, mx);
	}
	printf("%d\n", mx);
}