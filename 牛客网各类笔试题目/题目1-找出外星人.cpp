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
#include <functional>

using namespace::std;

struct campInfo
{
	int numStalls;
	int numAisies;
	vector<vector<int>> weightedMatrix;
	campInfo() :numStalls(0), numAisies(0) {}
	campInfo(int numStalls, int numAisies,
		vector<vector<int>> &weightedMatrix) :
		numStalls(numStalls), numAisies(numStalls),
		weightedMatrix(weightedMatrix) {}
};

struct IdxMST
{
	int idx;
	int msp;
	IdxMST(int idx, int msp) :idx(idx), msp(msp){}
	bool operator<(const IdxMST &others) const { return msp < others.msp; }
	bool operator>(const IdxMST &others) const { return msp > others.msp; }
};

int minKey(vector<int> &key, vector<bool> &mstSet)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < key.size(); v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

int getMST(vector<vector<int>> &Matrix)
{
	int verticesNum = Matrix.size();
	vector<int> parent(verticesNum);
	vector<int> key(verticesNum);
	vector<bool> mstSet(verticesNum);

	for (int i = 0; i < verticesNum; ++i)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;
	parent[0] = -1;
	for (int count = 0; count < verticesNum - 1; ++count) {
		int u = minKey(key, mstSet);
		mstSet[u] = true;
		for (int v = 0; v < verticesNum; ++v) {
			if (Matrix[u][v] && mstSet[v] == false && Matrix[u][v] < key[v])
				parent[v] = u, key[v] = Matrix[u][v];
		}
	}

	int result = 0;
	for (int i = 1; i < verticesNum; ++i)
		result += Matrix[i][parent[i]];
	return result;
}

pair<int, int> findAlien(int camps, int threshold,
	vector<campInfo> &camp_info)
{
	vector<IdxMST> vec;
	for (int i = 0; i < camps; ++i) {
		campInfo &temp = camp_info[i];
		int mst = getMST(temp.weightedMatrix);
		vec.emplace_back(i, mst);
	}

	sort(vec.begin(), vec.end(), greater<IdxMST>());
	pair<int, int> result;
	result.first = vec[threshold - 1].idx + 1;
	result.second = vec[threshold - 1].msp;

	return result;
}

void test1()
{
	int camps = 2;
	int threshold = 2;
	vector<campInfo> camp_info;
	vector<vector<int>> weightedMatrix1 =
	{ { 0, 10, 5 }, { 10, 0, 0 }, { 5, 0, 0 } };
	camp_info.emplace_back(3, 2, weightedMatrix1);

	vector<vector<int>> weightedMatrix2 =
	{ { 0, 10, 15, 0 }, { 10, 0, 0, 5 },
	{ 15, 0, 0, 20 }, { 0, 5, 20, 0 } };
	camp_info.emplace_back(4, 4, weightedMatrix2);

	pair<int, int> result;
	result = findAlien(camps, threshold, camp_info);
	cout << result.first << ' ' << result.second << endl;
}

void test2()
{
	int camps = 2;
	int threshold = 1;
	vector<campInfo> camp_info;
	vector<vector<int>> weightedMatrix1 =
	{ { 0, 10, 15, 0 }, { 10, 0, 0, 5 },
	{ 15, 0, 0, 20 }, { 0, 5, 20, 0 } };
	camp_info.emplace_back(4, 4, weightedMatrix1);

	vector<vector<int>> weightedMatrix2 =
	{ { 0, 10, 5, 20 }, { 10, 0, 0, 0 },
	{ 5, 0, 0, 0 }, { 20, 0, 0, 0 } };
	camp_info.emplace_back(4, 3, weightedMatrix2);

	pair<int, int> result;
	result = findAlien(camps, threshold, camp_info);
	cout << result.first << ' ' << result.second << endl;
}

int main(int argc, char* argv[])
{
	test1();
	test2();
	return 0;
}



