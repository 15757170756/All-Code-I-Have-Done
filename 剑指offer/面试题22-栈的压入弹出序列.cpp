#include <stack>
#include <iostream>

using namespace::std;

bool isPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool isOK = false;

	if (pPush && pPop && nLength > 0) {
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;

		stack<int> stackData;

		while (pNextPop - pPop < nLength) {
			while (stackData.empty() || stackData.top() != *pNextPop) {
				if (pNextPush - pPush == nLength)
					break;

				stackData.push(*pNextPush);
				++pNextPush;
			}

			if (stackData.top() != *pNextPop)
				break;

			stackData.pop();
			++pNextPop;
		}
		if (stackData.empty() && pNextPop - pPop == nLength)
			isOK = true;
	}

	return isOK;
}


class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        bool isOK = false;
		
		if (pushV.size() > 0 && popV.size() > 0) {
			stack<int> auxStack;
			vector<int>::const_iterator pushIter = pushV.begin();
			vector<int>::const_iterator pushEnd = pushV.end();
			vector<int>::const_iterator popIter = popV.begin();
			vector<int>::const_iterator popEnd = popV.end();

			while (popIter != popEnd) {
				while (auxStack.empty() || auxStack.top() != *popIter) {
					if (pushIter == pushEnd)
						break;
					auxStack.push(*pushIter);
					++pushIter;
				}
				if (auxStack.top() != *popIter)
					break;

				auxStack.pop();
				++popIter;
			}
			if (auxStack.empty() && popIter == popEnd)
				isOK = true;
		}
		return isOK;
    }
};



int main()
{
	int pPush[] = { 1, 2, 3, 4, 5 };
	int pPop1[] = { 4, 5, 3, 2, 1 };
	int pPop2[] = { 4, 3, 5, 1, 2 };
	int arrLength = sizeof(pPush) / sizeof(pPush[0]);
	cout << boolalpha << isPopOrder(pPush, pPop1, arrLength) << endl;
	cout << boolalpha << isPopOrder(pPush, pPop2, arrLength) << endl;

	return 0;
}