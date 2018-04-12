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

char* reverseSentence(char *pData, int n)
{
	if (pData != nullptr) {
		int length = strlen(pData);
		if (n < length && length > 0 && n > 0) {
			char *pFirstStart = pData;
			char *pFirstEnd = pData + n - 1;

			char *pSecondStart = pData + n;
			char *pSecondEnd = pData + length - 1;

			reverse(pFirstStart, pFirstEnd);
			reverse(pSecondStart, pSecondEnd);
			reverse(pFirstStart, pSecondEnd);
		}
	}

	return pData;
}

int main(int argc, char* argv[])
{
	char sentence[] = "abcdefg";
	cout << reverseSentence(sentence, 3) << endl;

	return 0;
}




