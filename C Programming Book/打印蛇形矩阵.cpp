/*
题目描述
题目说明

蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形。







样例输入

5

样例输出

1 3 6 10 15

2 5 9 14

4 8 13

7 12

11

接口说明

原型

void GetResult(int Num, char * pResult);

输入参数：

int Num：输入的正整数N

输出参数：

int * pResult：指向存放蛇形矩阵的字符串指针

指针指向的内存区域保证有效

返回值：

void

输入描述:
输入正整数N（N不大于100）

输出描述:
输出一个N行的蛇形矩阵。

示例1
输入
4
输出
1 3 6 10
2 5 9
4 8
7
*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>

using namespace::std;


int main(int argc, char* argv[])
{
	int n;
	while (cin >> n) {
		int sta = 1;
		for (int i = 1; i <= n; ++i) {
			sta += (i - 1);
			//cout << sta << endl;
			int sum = 0;
			for (int j = i; j <= n; ++j) {

				if (j == i)
					cout << sta << ' ';
				else {
					sum += j;
					cout << sta + sum << ' ';
				}
			}
			cout << endl;
		}
	}

	return 0;
}

/*
不通过
您的代码已保存
格式错误:您的程序输出的格式不符合要求（比如空格和换行与要求不一致）
case通过率为0.00%

华为的题目有些坑的 明明在VS上面调试蛮对的。
*/