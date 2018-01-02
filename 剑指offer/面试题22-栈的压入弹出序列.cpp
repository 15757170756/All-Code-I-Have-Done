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