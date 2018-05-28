#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <set>
#include <utility>

using namespace::std;

int getLineNum(int num, int timX, int timY, vector<pair<int, int>> &coordinates)
{
	set<float> ks;
	const float FLOAT_MAX = INT_MAX*1.0;
	for (int i = 0; i < num; ++i) {
		pair<int, int> &temp = coordinates[i];
		if (timX - temp.first == 0)
			ks.insert(FLOAT_MAX);
		else {
			float k = (timY - temp.second) * 1.0 / (timX - temp.first);
			ks.insert(k);
		}
	}

	return ks.size();

}

void test1()
{
	int num = 3;
	int timX = 0, timY = 0;
	vector<pair<int, int>> coordinates(num);
	coordinates[0].first = 1, coordinates[0].second = 1;
	coordinates[1].first = -1, coordinates[1].second = 1;
	coordinates[2].first = 2, coordinates[2].second = 3;
	cout << getLineNum(num, timX, timY, coordinates) << endl;
}

void test2()
{
	int num = 6;
	int timX = 0, timY = 0;
	vector<pair<int, int>> coordinates(num);
	coordinates[0].first = 2, coordinates[0].second = 2;
	coordinates[1].first = 3, coordinates[1].second = 3;
	coordinates[2].first = -4, coordinates[2].second = -8;
	coordinates[3].first = 8, coordinates[3].second = 8;
	coordinates[4].first = -1, coordinates[4].second = -1;
	coordinates[5].first = 5, coordinates[5].second = 8;
	cout << getLineNum(num, timX, timY, coordinates) << endl;
}

void test3()
{
	int num = 6;
	int timX = 0, timY = 0;
	vector<pair<int, int>> coordinates(num);
	coordinates[0].first = 0, coordinates[0].second = 2;
	coordinates[1].first = 3, coordinates[1].second = 3;
	coordinates[2].first = 0, coordinates[2].second = -8;
	coordinates[3].first = 0, coordinates[3].second = 8;
	coordinates[4].first = -1, coordinates[4].second = -1;
	coordinates[5].first = 5, coordinates[5].second = 8;
	cout << getLineNum(num, timX, timY, coordinates) << endl;
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	test3();
	return 0;
}



