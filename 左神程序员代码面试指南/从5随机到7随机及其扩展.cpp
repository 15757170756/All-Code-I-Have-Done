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

using namespace::std;

/*
rand1To5产生rand1To7
*/
int rand1To5()
{
	return (rand() % 5 + 1);
}
int rand1To7()
{
	int num = 0;
	do {
		num = (rand1To5() - 1) * 5 + rand1To5() - 1;
	} while (num > 20);
	return num % 7 + 1;
}


int rand01p()
{
	double p = 0.83;
	double b = rand() / (RAND_MAX + 1.0);
	return b < p ? 0 : 1;
}
int rand01()
{
	int num;
	do {
		num = rand01p();
	} while (num == rand01p());

	return num;
}
int rand0To3()
{
	return rand01() * 2 + rand01();
}
int rand1To6()
{
	int num = 0;
	do {
		num = rand0To3() * 4 + rand0To3();
	} while (num > 11);
	return num % 6 + 1;
}


int rand1ToM(int m)
{
	return (1 + rand() % m);
}
//将m进制数转成十进制数
int getNumFromMSysNum(vector<int> &mSysNum, int m)
{
	int res = 0;
	for (int i = 0; i < mSysNum.size(); ++i)
		res = res * m + mSysNum[i];
	return res;
}

//将value转成m进制数
vector<int> getMSysNum(int value, int m)
{
	vector<int> res(32, 0);
	int index = res.size() - 1;
	while (value != 0) {
		res[index--] = value % m;
		value /= m;
	}
	return res;
}

//等概率随机产生一个0~nMSys范围的数，
//用m进制表达
vector<int> getRanMSysNumLessN(vector<int> &nMSys, int m)
{
	vector<int> res(nMSys.size());
	int start = 0;
	while (0 == nMSys[start])
		++start;
	int index = start;
	bool lastEqual = true;
	while (index != nMSys.size()) {
		res[index] = rand1ToM(m) - 1;
		if (lastEqual) {
			if (res[index] > nMSys[index]) {
				index = start;
				lastEqual = true;
				continue;
			}
			else
				lastEqual = (res[index] == nMSys[index]);
		}
		++index;
	}
	return res;
}

int rand1ToN(int n, int m)
{
	vector<int> nMSys = getMSysNum(n - 1, m);
	vector<int> randNum = getRanMSysNumLessN(nMSys, m);
	return getNumFromMSysNum(randNum, m) + 1;
}

void test1()
{
	srand(time(0));
	for (int i = 0; i < 20; ++i)
		cout << rand1To7() << ' ';
	cout << endl << endl;
}

void test2()
{
	srand(time(0));
	for (int i = 0; i < 20; ++i)
		cout << rand1To6() << ' ';
	cout << endl << endl;
}

void test3()
{
	srand(time(0));
	for (int i = 0; i < 20; ++i)
		cout << rand1ToN(16, 3) << ' ';
	cout << endl << endl;
}



int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();

	return 0;
}



