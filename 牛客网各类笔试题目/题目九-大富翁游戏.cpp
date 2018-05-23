/*
我们来玩一个大富翁的游戏，在地图上有N个连续的城市，
城市对某件商品的售价为[V1,V2,V3...VN]，
你作为未来的大富翁看到其中的商机，
打起了倒卖商品赚取差价的主意。
约束条件：你只能顺序从第一个城市出发，
不能走回头路，每次只能交易一件商品，
再下次买入商品后必须卖掉之前买入的商品，
求你能赚取的最大财富。
比如：城市商品售价为[1,9,2,3,8]，最大财富为(9-1)+(8-2)=14；
城市商品售价为[9,8,3,2,1]，最大财富为0，因为你买啥都无法赚钱。

"输入的第一行指定用例数量T；
用例的第一行输入城市的个数n；
用例的第一行输入商品售价，以空格隔开；"

输出赚取的最大财富值

"1<=n<=100
1<=v<=100"

"Input:
2
5
1 9 2 3 8
5
9 8 3 2 1

Output:
14
0"


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

using namespace::std;


int getMaxValue(vector<int> &vec)
{
	int result = 0;
	int len = vec.size();
	for (int i = 0; i < len - 1; ++i) {
		int diff = vec[i + 1] - vec[i];
		if (diff > 0)
			result += diff;
		/*else
		++i;*/
	}
	return result;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> vec(n);
		for (int i = 0; i < n; ++i)
			cin >> vec[i];
		cout << getMaxValue(vec) << endl;
	}
}

int main(int argc, char* argv[])
{
	test1();

}