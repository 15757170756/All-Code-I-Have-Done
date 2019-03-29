/*
链接：https://ac.nowcoder.com/acm/contest/338/G
来源：牛客网

时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
This is a very simple problem! Your only job is to calculate a + b + c + d!
输入描述:
There are several cases.

In the first line, there is a single integer T.(T <= 200)

In the next T lines, each line contains four integers a, b, c and d(-2^61 <= a,b,c,d <=2^61)
输出描述:
output T lines.

Each line output one integer represent the answer of a + b + c + d
示例1
输入
复制
1
1 2 3 4
输出
复制
10
*/

#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>
#include <list>
#include <set>
#include <cstring>
#include <functional>
#include <deque>
#include <cstdio>
#include <iomanip>

using namespace::std;
//freopen("input.txt", "r+", stdin);

//struct Point2d
//{
//	double x;
//	double y;
//	Point2d(int xx, int yy) :
//		x(xx), y(yy) { }
//};

class BitInteger
{
public:
	BitInteger(){ }
	BitInteger(string ss):s(ss){ }
	BitInteger(const BitInteger& others)
	{
		s = others.s;
		num = others.num;
		isPlus = others.isPlus;
	}

	BitInteger& operator=(const BitInteger& others)
	{
		s = others.s;
		num = others.num;
		isPlus = others.isPlus;
		return *this;
	}
	~BitInteger() { }

	string s;
	vector<int> num;
	bool isPlus;
};

BitInteger operator+(BitInteger &lhs, BitInteger &rhs);
BitInteger operator-(BitInteger &lhs, BitInteger &rhs);
bool operator < (const BitInteger &lhs, const BitInteger &rhs);
bool operator > (const BitInteger &lhs, const BitInteger &rhs);
bool operator == (const BitInteger &lhs, const BitInteger &rhs);
//bool operator < (const BitInteger &lhs, const BitInteger &rhs);

BitInteger operator+(BitInteger &lhs, BitInteger &rhs)
{
	int i = 0; 
	BitInteger res;
	int carryBit = 0;
	int llens = lhs.num.size();
	int rlens = rhs.num.size();
	if ((lhs.isPlus && rhs.isPlus) || 
		(!lhs.isPlus && !rhs.isPlus)) {
		if (lhs.isPlus && rhs.isPlus)
			res.isPlus = true;
		else
			res.isPlus = false;
		for (i = 0; i <  llens&& i < rlens; ++i) {
			int temp = lhs.num[i] + rhs.num[i] + carryBit;
			if (temp > 9) {
				temp %= 10;
				carryBit = 1;
			}
			else
				carryBit = 0;
			res.num.push_back(temp);
			if (llens == rlens && carryBit && i == llens - 1)
				res.num.push_back(1);
		}
		while (i < llens) {
			int temp = lhs.num[i] + carryBit;
			if (temp > 9) {
				temp %= 10;
				carryBit = 1;
			}
			else
				carryBit = 0;
			res.num.push_back(temp);
			if (i == llens - 1 && carryBit)
				res.num.push_back(1);
			++i;
		}

		while (i < rlens) {
			int temp = rhs.num[i] + carryBit;
			if (temp > 9) {
				temp %= 10;
				carryBit = 1;
			}
			else
				carryBit = 0;
			res.num.push_back(temp);
			if (i == rlens - 1 && carryBit)
				res.num.push_back(1);
			++i;
		}
	}
	else {
		if (!lhs.isPlus && rhs.isPlus) {
			lhs.isPlus = true;
			if (lhs < rhs) {
				res = rhs - lhs;
				res.isPlus = true;
			}
			else {
				res = lhs - rhs;
				res.isPlus = false;
			}
		}

		if (lhs.isPlus && !rhs.isPlus) {
			rhs.isPlus = true;
			if (lhs > rhs) {
				res = lhs - rhs;
				res.isPlus = true;
			}
			else {
				res = rhs - lhs;
				res.isPlus = false;
			}
		}
	}
	return res;
}

BitInteger operator-(BitInteger &lhs, BitInteger &rhs)
{
	BitInteger res;
	if (!lhs.isPlus && rhs.isPlus) {
		res.isPlus = false;
		lhs.isPlus = true;
		res = lhs + rhs;
	}
	else if (lhs.isPlus && !rhs.isPlus) {
		res.isPlus = true;
		rhs.isPlus = true;
		res = lhs + rhs;
	}
	else if ((!lhs.isPlus && !rhs.isPlus) ||
		(lhs.isPlus && rhs.isPlus)){
		if ((lhs > rhs) ||
			(lhs < rhs) ||
			(lhs == rhs)) {
			if (lhs > rhs)
				res.isPlus = true;
			else if(lhs < rhs){
				res.isPlus = false;
				swap(lhs, rhs);
			}
			else {
				res.isPlus = true;
				res.num.push_back(0);
				return res;
			}
			int carryBit = 0;
			int i;
			for (i = 0; i < rhs.num.size(); ++i) {
				int temp = lhs.num[i] - rhs.num[i] - carryBit;
				if (temp < 0) {
					temp += 10;
					carryBit = 1;
				}
				else
					carryBit = 0;
				res.num.push_back(temp);
			}
			while (i < lhs.num.size()) {
				if (carryBit) {
					int temp = lhs.num[i] - 1;
					if(temp > 0)
						res.num.push_back(temp);
					carryBit = 0;
				}
				else
					res.num.push_back(lhs.num[i]);
				++i;
			}
		}
	}

	return res;
}

bool operator < (const BitInteger &lhs, const BitInteger &rhs)
{
	if (lhs.isPlus && !rhs.isPlus)
		return false;
	else if (!lhs.isPlus && rhs.isPlus)
		return true;
	else if (lhs.isPlus && rhs.isPlus) {
		if (lhs.num.size() != rhs.num.size())
			return lhs.num.size() < rhs.num.size();

		int len = lhs.num.size();
		for (int i = len - 1; i >= 0; --i) 
			if (lhs.num[i] != rhs.num[i])
				return lhs.num[i] < rhs.num[i];

		return false;
	
	}

	else if (!lhs.isPlus && !rhs.isPlus) {
		if (lhs.num.size() != rhs.num.size())
			return lhs.num.size() > rhs.num.size();

		int len = lhs.num.size();
		for (int i = len - 1; i >= 0; ++i) {
			if (lhs.num[i] != rhs.num[i])
				return lhs.num[i] > rhs.num[i];
		}
		return false;
	}
	return false;
}

bool operator > (const BitInteger &lhs, const BitInteger &rhs)
{
	return rhs < lhs;
}

bool operator <= (const BitInteger &lhs, const BitInteger &rhs)
{
	return !(lhs < rhs);
}

bool operator >= (const BitInteger &lhs, const BitInteger &rhs)
{
	return !(lhs > rhs);
}

bool operator == (const BitInteger &lhs, const BitInteger &rhs)
{
	return !(lhs > rhs) && !(rhs > lhs);
}

bool operator != (const BitInteger &lhs, const BitInteger &rhs)
{
	return lhs > rhs || rhs > lhs;
}

istream &operator>>(istream &os, BitInteger &item)
{
	os >> item.s;
	if (item.s[0] == '-') {
		item.isPlus = false;
		item.s.erase(item.s.begin());
	}
	else
		item.isPlus = true;

	int len = item.s.size();
	for (int i = len - 1; i >= 0; --i) {
		item.num.push_back(item.s[i] - '0');
	}
	return os;
}

ostream &operator<<(ostream &os, BitInteger &item)
{
	if (!item.isPlus) {
		if(item.num.size() > 0 && 
			item.num[item.num.size() - 1] != 0)
			os << '-';
		int n = item.num.size();
		for (int i = n - 1; i >= 0; --i)
			os << item.num[i];
	}
	else {
		int n = item.num.size();
		for (int i = n - 1; i >= 0; --i)
			os << item.num[i];
	}

	return os;
}

int main() 
{
	freopen("input.txt", "r+", stdin);
	
	/*int n, q;
	cin >> n >> q;
	vector<Point2d> points(n);
	for (int i = 0; i < n; ++i) {
		cin >> points[i].x >> points[i].y;
	}
	vector<pair<int, int>> vecPair(q);
	for (int i = 0; i < q; ++i)
		cin >> vecPair[i].first >> vecPair[i].second;*/

	int n;
	cin >> n;
	while (n--) {
		BitInteger a, b, c, d;
		cin >> a >> b >> c >> d;
		BitInteger e;
		e = a + b;
		e = e + c;
		e = e + d;
		cout << e << endl;
	}

	return 0;
}



/*
通过
您的代码已保存
答案正确:恭喜！
您提交的程序通过了所有的测试用例
*/