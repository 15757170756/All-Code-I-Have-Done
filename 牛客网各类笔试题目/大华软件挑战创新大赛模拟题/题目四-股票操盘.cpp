/*
某股票操盘手账户里有N支股票，股价互不等，分别为v1,v2...vn;
每支股票的持有股数为m1,m2...mn。现在操盘手要回笼资金需要卖出股票，
假设卖出价格即为当前股价，请问能回笼多少种不同的资金量。
比如：两支股票，股价分别为10、11,数量为1、2，
则能回笼0、10、11、22、21、32，总共6种资金量

"输入的第一行指定用例数量T；
用例的第一行输入股票种类n；
用例的第二行输入股票的价格，以空格隔开；
用例的第三行输入股票的数量，已空格隔开；"

输出不同资金量的个数

"1<=n<=10
1<=v<=20
1<=m<=6"

"Input:
1
2
10 11
1 2

Output:
6"

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

using namespace::std;

bool increae(vector<bool> &bs)
{
	for (size_t i = 0; i != bs.size(); ++i) {
		bs[i] = !bs[i];
		if (bs[i] == true)
			return true;
	}
	return false;
}

int powersets(const vector<int> &v)
{
	vector<bool> bitset(v.size());
	vector<vector<int>> resultVec;
	do {
		vector<int> temp;
		temp.clear();
		for (size_t i = 0; i != v.size(); ++i) {
			if (bitset[i]) {
				temp.push_back(v[i]);
			}
		}
		if (!temp.empty())
			resultVec.push_back(temp);
	} while (increae(bitset));
	set<int> setVec;
	for (int i = 0; i < resultVec.size(); ++i) {
		vector<int> tempVec = resultVec[i];
		int sum = accumulate(tempVec.begin(), tempVec.end(), 0);
		setVec.emplace(sum);
	}
	return setVec.size() + 1;
}


int numMoneyMount(vector<int> &price, vector<int> &num)
{
	vector<int> result;
	int n = price.size();
	for (int i = 0; i < n; ++i) {
		int temp = num[i];
		for (int j = 0; j < temp; ++j)
			result.push_back(price[i]);
	}

	return powersets(result);
}

void test1()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<int> price(n), num(n);
		for (int i = 0; i < n; ++i)
			cin >> price[i];
		for (int i = 0; i < n; ++i)
			cin >> num[i];
		cout << numMoneyMount(price, num) << endl;
	}
}

int main(int argc, char* argv[])
{
	clock_t t0 = clock();
	test1();
	//cout << (clock() - t0) << endl;
	cout << 1000.0 * (clock() - t0) / CLOCKS_PER_SEC << " ms\n";
	return 0;
}























//参考答案
/* 算法概述
* 股票种类n,股价v[i],股票数量m[i]；
* v1 v2 v3 v4 .... vn
* m1 m2 m3 m4 .... mn
* 假设前i种股票能套现出不同资金量的数目为Q[i]，那么Q[i]可以这么计算：
在Q[i-1]的基础上，对Q[i-1]套现资金基础上，分别卖出k股i类型股票，在卖出过程中去重。
* Q[i] = Q[i-1]+k*v[i]-卖出中重复的个数，其中0<=k<=m[i]
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
using namespace std;


int main(void)
{
	clock_t t0 = clock();
	int t;
	cin >> t;
	while (t--) {
		int n;	//股票种类数
		cin >> n;
		int *v = new int[n]; //每种股票的股价 
		int *m = new int[n]; //每种股票的股数
		for (int i = 0; i<n; i++)
			cin >> v[i];
		for (int i = 0; i<n; i++)
			cin >> m[i];

		vector<int> money; //所有卖出股票的资金量
		/*先将第一种股票所卖出的资金数入列*/
		money.push_back(0);
		for (int i = 1; i <= m[0]; i++) 
			if (i * v[0] != 0)
				money.push_back(i*v[0]);

		//前多少种股票
		for (int i = 1; i < n; i++) {
			int len = money.size();//记录已经卖出的资金量数
			for (int j = 1; j <= m[i]; j++) { //遍历该股票的股数
				for (int z = 0; z<len; z++) {
					int moneyTmp = money[z] + j*v[i];//将该股票的抛售的资金与前面所有的资金数相加
					if (find(money.begin(), money.end(), moneyTmp)
						== money.end())//如果没有这个资金数则将这个资金入列
						money.push_back(money[z] + j*v[i]);
				}
			}
		}
		cout << money.size() << endl;
	}
	cout << 1000.0 * (clock() - t0) / CLOCKS_PER_SEC << " ms\n";

	return 0;
}
