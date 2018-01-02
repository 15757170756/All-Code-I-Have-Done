#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace::std;

bool isPopOrder(const vector<int>& pPush, const vector<int>& pPop)
{
	bool isOK = false;

	if (pPush.size() > 0 && pPop.size() > 0) {
		int nLength = pPush.size();
		vector<int>::const_iterator pNextPush = pPush.begin();
		vector<int>::const_iterator pNextPop = pPop.begin();

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
	vector<int> pPush = { 1, 2, 3, 4, 5 };
	vector<vector<int>> resultVec;
	permutations(pPush, resultVec);
	int cnt = 0;
	for (int i = 0; i < resultVec.size(); ++i) {
		vector<int>& temp = resultVec[i];
		if (isPopOrder(pPush, temp)) {
			++cnt;
			copy(temp.begin(), temp.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
		}

	}
	cout << "total:" << cnt << endl;


	return 0;
}