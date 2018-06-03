/*
题目2 : 被遗忘的整数
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
小 Hi 有一个正整数 n，但他忘了这个数是啥了。
他只记得 n 的所有约数的平均数是 a，
n 的所有约数的调和平均数是 h ，且 a 和 h 都是正整数，
现在小 Hi 想要你找出 n 的值。保证 n 存在，且小于等于 108

注：

n个数a1,a2..an的算术平均数为∑ai / n

n个数a1,a2..an的调和平均数为n / ∑(1/ai)

输入
第一行两个正整数 a , h

输出
输出一个正整数 n

样例提示
6的约数有 1 ， 2 ，3，6，算术平均数为 3，调和平均数为 2

样例输入
3 2
样例输出
6
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
#include <climits>

using namespace std;


int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	int a, h;
	scanf("%d%d", &a, &h);
	printf("%d\n", a*h);

	return 0;
}

/*
结果:Accepted
得分:100 / 100

有毒的。。。
*/