/*
N个国家参加了世界贸易博览会，每个国家都有各自的雄位及独立营地，在此期间你被
任命为安保人员。在任意个营地内，位通过非负长度的通道连接，可以沿着一个
通道或一组通道在各雄位之间通行。人们可以从任意一个推位进出营地
营地的Na是指营地内到达任意推位需要通过的通道的最小长度总和。你得到情报，
世界贸易博览会已遭到外星人的入侵，所有外星人潜伏在某个营地中。为了找到外星
人，你可以找出具有第k个Nva数组最大值的营地，该营地即外星人也。
输入
函数方法的输入包括三个参数
camps，表示博览会中营地数目（N）的整数。
threshold，表示用于大最大值索引（K）的塾数。
camp＿info，个列表，表示N个营地的信息和每个营地内推位的连通性。
输出
返回个列表，该列表由两个整数组成，分別表示含有外星人的国家的索引和其
Nval
约束条件
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