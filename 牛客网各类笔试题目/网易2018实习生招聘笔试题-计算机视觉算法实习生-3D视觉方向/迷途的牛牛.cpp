/*
[编程题] 迷路的牛牛
时间限制：1秒

空间限制：32768K

牛牛去犇犇老师家补课，出门的时候面向北方，但是现在他迷路了。虽然他手里有一张地图，但是他需要知道自己面向哪个方向，请你帮帮他。 
输入描述:
每个输入包含一个测试用例。
每个测试用例的第一行包含一个正整数，表示转方向的次数N(N<=1000)。
接下来的一行包含一个长度为N的字符串，由L和R组成，L表示向左转，R表示向右转。


输出描述:
输出牛牛最后面向的方向，N表示北，S表示南，E表示东，W表示西。

输入例子1:
3
LRR

输出例子1:
E

例子说明1:

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
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	char *direction = new char[n];
	scanf("%s", direction);
	char dire[4] = { 'N', 'S', 'E', 'W' };
	char curDire = ' ';
	for (int i = 0; i < n; ++i) {
		if (i == 0) {
			if (direction[i] == 'L')
				curDire = 'W';
			else if (direction[i] == 'R')
				curDire = 'E';
		}
		else {
			if (curDire == 'W') {
				if (direction[i] == 'L')
					curDire = 'S';
				else if (direction[i] == 'R')
					curDire = 'N';
			}

			else if (curDire == 'E') {
				if (direction[i] == 'L')
					curDire = 'N';
				else if (direction[i] == 'R')
					curDire = 'S';
			}

			else if (curDire == 'S') {
				if (direction[i] == 'L')
					curDire = 'E';
				else if (direction[i] == 'R')
					curDire = 'W';
			}

			else if (curDire == 'N') {
				if (direction[i] == 'L')
					curDire = 'W';
				else if (direction[i] == 'R')
					curDire = 'E';
			}
		}
	}
	printf("%c\n", curDire);
	return 0;
}


/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
算法工程师的编程题的确简单。。。 o(╥﹏╥)o
*/