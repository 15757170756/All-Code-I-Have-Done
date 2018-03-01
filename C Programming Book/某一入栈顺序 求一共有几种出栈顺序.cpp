#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace::std;

template<typename T>
bool isPopOrder(const vector<T>& pPush, const vector<T>& pPop)
{
	bool isOK = false;

	if (pPush.size() > 0 && pPop.size() > 0) {
		int nLength = pPush.size();
		vector<T>::const_iterator pNextPush = pPush.begin();
		vector<T>::const_iterator pNextPop = pPop.begin();

		stack<int> stackData;

		while (pNextPop - pPop.begin() < nLength) {
			while (stackData.empty() || stackData.top() != *pNextPop) {
				if (pNextPush - pPush.begin() == nLength)
					break;

				stackData.push(*pNextPush);
				++pNextPush;
			}

			if (stackData.top() != *pNextPop)
				break;

			stackData.pop();
			++pNextPop;
		}
		if (stackData.empty() && pNextPop - pPop.begin() == nLength)
			isOK = true;
	}

	return isOK;
}

template<typename T>
void permutations(vector<T> v, vector<vector<T>> &resultVec)
{
	sort(v.begin(), v.end());
	do {
		resultVec.push_back(v);
	} while (next_permutation(v.begin(), v.end()));
}

int main()
{
	vector<char> pPush = { 'A', 'B', 'C', 'D' };
	vector<vector<char>> resultVec;
	permutations(pPush, resultVec);
	int cnt = 0;
	for (int i = 0; i < resultVec.size(); ++i) {
		vector<char>& temp = resultVec[i];
		if (isPopOrder(pPush, temp)) {
			++cnt;
			copy(temp.begin(), temp.end(), ostream_iterator<char>(cout, " "));
			cout << endl;
		}

	}
	cout << "total:" << cnt << endl;

	return 0;
}