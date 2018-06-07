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













/*
思想：

1：牛牛吃1，牛牛胜

2：牛牛吃1，羊羊吃1，羊胜

3：牛牛吃1，羊羊吃1，牛牛吃1，牛牛胜

4：牛牛吃4，牛牛胜

5：不管是牛牛吃1还是吃4，最后都是羊羊胜

6：1,1,4随机排序，都是牛羊牛的吃草循序，
最后都是牛牛胜；也就是说，将1和4作为最后的吃草份数，
在不计最后的1和4时，之前的份数最终是谁吃完的，就是谁胜，
所以又进入了一个1和4的循环（也就是周期为5）；
也就是说，当5以后时，牛牛和羊羊都会以最优的方式来吃，
在最后都会使自己吃完剩下的数为5，那么不管是谁，
最后胜的都是自己，基本上是以5为周期来确定，这样问题就解决了。

有人可能会说那17（16+1）、65（64+1）等等，
这个就不能确定了？但是要注意，题目是说最优吃草方式，
比如说，当羊羊吃完还剩17时，牛牛如果吃16或1时，
那么羊羊肯定是胜利者，所以牛牛不会选择吃16或1，
所以他会选择吃4，这时就又会进入支持1和4的循环中了，
也就是5份为一轮。65和129之后都是同样的道理，
感兴趣的可以自己去算一下，但是要注意是最优吃草方式，
所以让对方赢的可能是在遵循规则下逼不得已出现的。
*/

//数学问题。。。
#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int f = n % 5;
		switch (f) {
		case 1:cout << "niu\n"; break;
		case 2:cout << "yang\n"; break;
		case 3:cout << "niu\n"; break;
		case 4:cout << "niu\n"; break;
		case 0:cout << "yang\n"; break;
		}
	}

}








#include<stdio.h>

int dp[10], n, x, i, j;

int main()
{
	freopen("input.txt", "r", stdin);
	for (i = 1; i < 10; i++){
		int flag = 0;
		for (j = 1; j <= i; j *= 4)
			if (dp[i - j] == 0) 
				flag = 1;
		dp[i] = flag;
	}
	for (scanf("%d", &n), i = 0; i < n; i++)
		scanf("%d", &x), printf("%s\n", dp[x % 10] ? "niu" : "yang");
}