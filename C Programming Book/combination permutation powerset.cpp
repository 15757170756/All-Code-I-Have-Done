/***************************************
使用C++ STL Algorithm等实现排列组合、
幂级数,主要使用的是Algorithm中的
next_permutation
****************************************/
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace::std;

template<typename BidirIt>
bool my_next_permutation(BidirIt first, BidirIt last);

template<typename T>
void permutations(vector<T> v, vector<vector<T>> &resultVec);

template<typename T>
void combinations(const vector<T> &v, size_t count, vector<vector<int>> &resultVec);

bool increae(vector<bool> &bs);

template <typename T>
void powersets(const vector<T> &v, vector<vector<T>> &resultVec);

int main()
{
	vector<int> v = { 9, 6, 3, 4, 5 };
	//测试permutations
	cout << "测试permutations:" << endl;
	vector<vector<int>> permutationResultV;
	permutations(v, permutationResultV);
	for (int i = 0; i < permutationResultV.size(); ++i) {
		cout << i + 1 << ":\t";
		vector<int> temp = permutationResultV[i];
		for (int j = 0; j < temp.size(); ++j) {
			cout << temp[j] << " ";
		}
		cout << endl;
	}

	//测试combinations
	cout << endl << "测试combinations:" << endl;
	vector<vector<int>> combiResultVec;
	combinations(v, 4, combiResultVec);
	for (int i = 0; i < combiResultVec.size(); ++i) {
		cout << i + 1 << ":\t";
		vector<int> temp = combiResultVec[i];
		for (int j = 0; j < temp.size(); ++j) {
			cout << temp[j] << " ";
		}
		cout << endl;
	}

	//测试powersets
	cout << endl << "测试powersets:" << endl;
	vector<vector<int>> powersetResultVec;
	powersets(v, powersetResultVec);
	for (int i = 0; i < powersetResultVec.size(); ++i) {
		cout << i + 1 << ":\t";
		vector<int> temp = powersetResultVec[i];
		for (int j = 0; j < temp.size(); ++j) {
			cout << temp[j] << " ";
		}
		cout << endl;
	}
}



template<typename T>
void permutations(vector<T> v, vector<vector<T>> &resultVec)
{
	sort(v.begin(), v.end());
	do {
		resultVec.push_back(v);
	} while (my_next_permutation(v.begin(), v.end()));
}

template<typename T>
void combinations(const vector<T> &v, size_t count, vector<vector<int>> &resultVec)
{
	assert(count <= v.size());
	vector<bool> bitset(v.size() - count, 0);
	bitset.resize(v.size(), 1);
	do {
		vector<int> temp;
		temp.clear();
		for (size_t i = 0; i != v.size(); ++i) {
			if (bitset[i]) {
				temp.push_back(v[i]);
				//cout << v[i] << " ";
			}
		}
		resultVec.push_back(temp);
		//cout << endl;
		//for (int i = 0; i < bitset.size(); ++i)
		//	cout << bitset[i] << " ";
		//cout << endl;
	} while (my_next_permutation(bitset.begin(), bitset.end()));
}

bool increae(vector<bool> &bs)
{
	for (size_t i = 0; i != bs.size(); ++i) {
		bs[i] = !bs[i];
		if (bs[i] == true)
			return true;
	}
	return false;
}

template <typename T>
void powersets(const vector<T> &v, vector<vector<T>> &resultVec)
{
	vector<bool> bitset(v.size()，false);

	do {
		vector<int> temp;
		temp.clear();
		for (size_t i = 0; i != v.size(); ++i) {
			if (bitset[i]) {
				temp.push_back(v[i]);
				//cout << v[i] << " ";
			}
		}
		if (!temp.empty())
			resultVec.push_back(temp);
		//cout << endl;
		//for (int i = 0; i < bitset.size(); ++i)
		//	cout << bitset[i] << " ";
		//cout << endl;
	} while (increae(bitset));
}


//Algorithm中next_permutation的实现

template<typename BidirIt>
bool my_next_permutation(BidirIt first, BidirIt last)
{
	if (first == last) return false;
	BidirIt i = last;
	if (first == --i) return false;

	while (true) {
		BidirIt i1, i2;

		i1 = i;
		if (*--i < *i1) {
			i2 = last;
			while (!(*i < *--i2));
			std::iter_swap(i, i2);
			std::reverse(i1, last);
			return true;
		}
		if (i == first) {
			std::reverse(first, last);
			return false;
		}
	}
} 