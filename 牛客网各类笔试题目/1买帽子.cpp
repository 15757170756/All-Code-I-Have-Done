/*
时间限制：1秒

空间限制：32768K

度度熊想去商场买一顶帽子，商场里有N顶帽子，有些帽子的价格可能相同。
度度熊想买一顶价格第三便宜的帽子，问第三便宜的帽子价格是多少？
输入描述 :
首先输入一个正整数N（N <= 50），
接下来输入N个数表示每顶帽子的价格（价格均是正整数，且小于等于1000）


输出描述 :
如果存在第三便宜的帽子，请输出这个价格是多少，否则输出 - 1

输入例子1 :
	  10
	  10 10 10 10 20 20 30 30 40 40

  输出例子1 :
		30
		*/


#include <set>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace::std;

int main()
{
	int k = 3;
	int N, temp;
	cin >> N;
	set<int> arrSet;
	while (N--) {
		cin >> temp;
		arrSet.insert(temp);
	}

	vector<int> arrVec(arrSet.begin(), arrSet.end());
	if (arrVec.size() < k)
		cout << -1 << endl;
	else
		cout << arrVec[k - 1] << endl;

	//set<int>::const_iterator ite = arrSet.cbegin();
	//while (ite != arrSet.cend()) {
	//	cout << *ite << ' ';
	//	++ite;
	//}
}