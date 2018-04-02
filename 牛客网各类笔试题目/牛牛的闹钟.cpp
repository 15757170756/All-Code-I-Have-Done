/*
[编程题] 牛牛的闹钟
时间限制：1秒

空间限制：32768K

牛牛总是睡过头，所以他定了很多闹钟，只有在闹钟响的时候他才会醒过来并且决定起不起床。从他起床算起他需要X分钟到达教室，上课时间为当天的A时B分，请问他最晚可以什么时间起床
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

*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace::std;

struct timeDis
{
	int hour;
	int miu;
	timeDis(int hour = 0, int miu = 0) : hour(hour), miu(miu){}

};

timeDis diff(const timeDis &t1, int mins)
{
	int hours = 0;
	if (mins > 60) {
		hours = 1;
		mins -= 60;
	}

	int dM = t1.miu - mins;
	int dH = t1.hour - hours;
	if (dM < 0){
		--dH;
		dM = t1.miu + mins;
	}
	return timeDis(dH, dM);
}

int diff(timeDis &t1, timeDis &t2)
{
	int mins1 = t1.miu + t1.hour * 60;
	int mins2 = t2.miu + t2.hour * 60;
	return mins1 - mins2;
}

int main(int argc, char* argv[])
{
	ifstream in("input.txt");

	int n;
	cin >> n;

	vector<timeDis> vecTime(n);
	for (int i = 0; i < n; ++i)
		cin >> vecTime[i].hour >> vecTime[i].miu;

	int xMinus;
	cin >> xMinus;
	int classAHour, classBMin;
	cin >> classAHour >> classBMin;

	timeDis classHour(classAHour, classBMin);

	timeDis d = diff(classHour, xMinus);
	int dMin = diff(vecTime[0], d);
	int index = 0;
	for (int i = 1; i < n; ++i) {
		int thisMin = diff(vecTime[i], d);
		if (thisMin <= 0 && thisMin > dMin) {
			dMin = thisMin;
			index = i;
		}
	}
	cout << vecTime[index].hour << ' ' << vecTime[index].miu << endl;
	return 0;
}















作者：NotDeep
链接：https ://www.nowcoder.com/discuss/70736
来源：牛客网

#include <bits/stdc++.h>

using namespace std;

int h[105], m[105];
int main() {
	int n, x;
	int ans1 = 0, ans2 = 0, temp1, temp2;
	int a, b;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &h[i], &m[i]);
	scanf("%d", &x);
	scanf("%d%d", &a, &b);
	for (int i = 0; i < n; i++) {
		temp2 = m[i] + x;
		temp1 = h[i] + temp2 / 60;
		temp2 = temp2 % 60;
		if (temp1 < a || (temp1 == a && temp2 <= b)) {
			if (h[i] > ans1 || (h[i] == ans1 && m[i] > ans2)) {
				ans1 = h[i];
				ans2 = m[i];
			}
		}
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
