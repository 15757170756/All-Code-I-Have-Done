#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;

void reverse(char *pBegin, char *pEnd)
{
	assert(pBegin != nullptr && pEnd != nullptr);
	while (pBegin < pEnd) {
		char temp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = temp;
		++pBegin, --pEnd;
	}
}

char* reverseSentence(char *pData)
{
	assert(pData != nullptr);
	char *pBegin = pData;
	char *pEnd = pData;
	while (*pEnd != '\0')
		++pEnd;
	--pEnd;
	reverse(pBegin, pEnd);
	pBegin = pEnd = pData;
	while (*pBegin != '\0') {
		if (*pBegin == ' ') {
			++pBegin;
			++pEnd;
		}
		else if (*pEnd == ' ' || *pEnd == '\0') {
			reverse(pBegin, --pEnd);
			pBegin = ++pEnd;
		}
		else
			++pEnd;
	}
	return pData;
}

int main(int argc, char* argv[])
{
	char sentence[] = "I am LiChaoFeng and I love GaoQianYun!";
	cout << reverseSentence(sentence) << endl;

	return 0;
}




