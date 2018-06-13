/*
题目1 : 比赛日程安排
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
H国编程联赛中有N只队伍，编号1~N。 他们计划在2018年一共进行M场一(队)对一(队)的比赛。

为了让参赛队员能得到充分的休息，联赛组委会决定：每支队伍连续两场比赛之间至少间隔一天。
也就是如果A队1月1日参加了一场比赛，那么下一场比赛最早安排在1月3日。

给定M场比赛的时间和参赛的两支队伍，请你判断这个日程安排是否可行。

输入
第一行包含一个整数T，代表测试数据组数。(1 ≤ T ≤ 10)

对于每组数据，第一行包含两个整数N和M。(1 ≤ N ≤ 50, 1 ≤ M ≤ 1000)

以下M行每行描述一场比赛，包含比赛日期(格式MM-DD)，以及2支参赛队伍的编号。

输出
对于每组数据输出YES或者NO，代表日程安排是否可行。

样例输入
2
3 3
01-01 1 2
01-03 1 3
01-05 2 3
4 4
02-01 4 3
01-30 4 1
01-31 1 2
01-30 2 3
样例输出
YES
NO
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace::std;

struct matchArrange {
	string dateTime;
	int team1;
	int team2;
	int dayInaYear;
};

int dateTimetoInt(string dateTime)
{
	int months[12] = { 31, 29, 30, 31, 31, 30,
		31, 31, 30, 31, 30, 31 };
	int month = stoi(dateTime.substr(0, 2));
	int day = stoi(dateTime.substr(3, 2));
	int dayInaYear = 0;
	for (int i = 0; i < month - 1; ++i)
		dayInaYear += months[i];

	return (dayInaYear + day);
}

bool isOK(matchArrange* matchs, int N, int M)
{
	for (int i = 0; i < M; ++i) {
		for (int j = i + 1; j < M; ++j) {
			if (abs(matchs[i].dayInaYear -
				matchs[j].dayInaYear) > 1)
				continue;
			else {
				if (matchs[i].team1 == matchs[j].team1 ||
					matchs[i].team1 == matchs[j].team2 ||
					matchs[i].team2 == matchs[j].team2 ||
					matchs[i].team2 == matchs[j].team1)
					return false;
			}
		}
	}
	return true;
}

int main()
{
	int T, N, M;
	cin >> T;
	while (T--) {
		cin >> N >> M;
		matchArrange* matchs = new matchArrange[M];
		for (int i = 0; i < M; ++i) {
			cin >> matchs[i].dateTime
				>> matchs[i].team1 >> matchs[i].team2;
			matchs[i].dayInaYear =
				dateTimetoInt(matchs[i].dateTime);
		}
		if (isOK(matchs, N, M))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
		delete[] matchs;
	}

	return 0;
}