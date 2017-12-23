#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace::std;

bool isPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool bPossible = false;
	//进行边界处理
	if (!pPush && !pPop && nLength > 0) {
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;

		stack<int> auxStack;
		while (pNextPop - pPop < nLength) {
			while (auxStack.empty() ||
				auxStack.top() != *pNextPop) {
				auxStack.push(*pNextPush);
				++pNextPush;
			}

			if (auxStack.top() != *pNextPop)
				break;

			auxStack.pop();
			++pNextPop;
		}
		if (auxStack.empty() && pNextPop - pPop == nLength)
			bPossible = true;
	}

	return bPossible;
}



int main()
{
	stack<int> s;
	s.top();

	return 0;
}



