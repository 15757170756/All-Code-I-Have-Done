/*
https://www.nowcoder.com/question/next?pid=8246419&qid=137859&tid=13940218

时间限制：1秒

空间限制：32768K

牛牛和羊羊都很喜欢青草。今天他们决定玩青草游戏。
最初有一个装有n份青草的箱子,牛牛和羊羊依次进行,牛牛先开始。
在每个回合中,每个玩家必须吃一些箱子中的青草,
所吃的青草份数必须是4的x次幂,比如1,4,16,64等等。
不能在箱子中吃到有效份数青草的玩家落败。
假定牛牛和羊羊都是按照最佳方法进行游戏,请输出胜利者的名字。
输入描述:
输入包括t+1行。
第一行包括一个整数t(1 ≤ t ≤ 100),表示情况数.
接下来t行每行一个n(1 ≤ n ≤ 10^9),表示青草份数


输出描述:
对于每一个n,如果牛牛胜利输出"niu",如果羊羊胜利输出"yang"。

输入例子1:
3
1
2
3

输出例子1:
niu
yang
niu
*/



#include <iostream>
#include <cmath>
#include <string>

using namespace::std;

string eatGrass(int n)
{
	string res;
	int cnt = 0;
	int temp = n;
	while (1) {
		for (int j = 0, i = 0; j < temp && n >= 0; ++j) {
			int maxEatNum = static_cast<int>(pow(4, i));
			if (n / maxEatNum >= 1 &&
				n / (maxEatNum * 4) == 0) {
				n = n - maxEatNum;
				++cnt;
				i = 0;
			}
			else
				++i;
		}
		if (cnt % 2 == 1) {
			res = "niu";
			return res;
		}
		else {
			res = "yang";
			return res;
		}
	}
}

int main()
{
	int t, n;
	cin >> t;
	while (t--) {
		cin >> n;
		cout << eatGrass(n) << endl;
	}

}

/*
您的代码已保存
运行超时:您的程序未能在规定时间内运行结束，
请检查是否循环有错或算法复杂度过大。
case通过率为10.00%
*/