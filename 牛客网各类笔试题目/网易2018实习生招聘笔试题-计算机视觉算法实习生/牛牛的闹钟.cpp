/*
[编程题] 牛牛的闹钟
时间限制：1秒

空间限制：32768K

牛牛总是睡过头，所以他定了很多闹钟，
只有在闹钟响的时候他才会醒过来并且决定起不起床。
从他起床算起他需要X分钟到达教室，上课时间为当天的A时B分，请问他最晚可以什么时间起床 
输入描述:
每个输入包含一个测试用例。
每个测试用例的第一行包含一个正整数，表示闹钟的数量N(N<=100)。
接下来的N行每行包含两个整数，表示这个闹钟响起的时间为Hi(0<=A<24)时Mi(0<=B<60)分。
接下来的一行包含一个整数，表示从起床算起他需要X(0<=X<=100)分钟到达教室。
接下来的一行包含两个整数，表示上课时间为A(0<=A<24)时B(0<=B<60)分。
数据保证至少有一个闹钟可以让牛牛及时到达教室。


输出描述:
输出两个整数表示牛牛最晚起床时间。

输入例子1:
3 
5 0 
6 0 
7 0 
59 
6 59

输出例子1:
6 0

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

const int maxn = 110;
int Hi[maxn];
int Mi[maxn];
int totalMi[maxn];

int main()
{
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", Hi + i, Mi + i);
		totalMi[i] = 60 * Hi[i] + Mi[i];
	}
	int x;
	scanf("%d", &x);
	int A, B;
	scanf("%d%d", &A, &B);
	int miniuniu = A * 60 + B;
	int lastGetup = miniuniu - x;
	int minN = INT_MAX;
	int minIdx = -1;
	for (int i = 0; i < n; ++i) {
		if (lastGetup - totalMi[i] >= 0) {
			int curMin = lastGetup - totalMi[i];
			if (curMin < minN) {
				minN = curMin;
				minIdx = i;
			}
		}
	}
	printf("%d %d\n", Hi[minIdx], Mi[minIdx]);

	return 0;
}

/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/