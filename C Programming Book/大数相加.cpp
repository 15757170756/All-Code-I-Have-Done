#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <deque>

using namespace::std;

const int MAXLEN = 201;

int an1[MAXLEN], an2[MAXLEN];
char szLine1[MAXLEN], szLine2[MAXLEN];

int add(int nMaxlen, int *an1, int *an2)
{
	int nHighestPos = 0;
	for (int i = 0; i < nMaxlen; ++i) {
		an1[i] += an2[i];
		if (an1[i] >= 10) {
			an1[i] -= 10;
			++an1[i + 1];
		}
		if (an1[i])
			nHighestPos = i;
	}

	return nHighestPos;
}

void test1()
{

}


int main(int argc, char* argv[])
{
	scanf("%s", szLine1);
	scanf("%s", szLine2);
	int i, j;
	memset(an1, 0, sizeof(an1));
	memset(an2, 0, sizeof(an2));

	int nLen1 = strlen(szLine1);
	for (int j = 0, i = nLen1 - 1;
		i >= 0; --i)
		an1[j++] = szLine1[i] - '0';

	int nLen2 = strlen(szLine2);
	for (int j = 0, i = nLen2 - 1;
		i >= 0; --i)
		an2[j++] = szLine2[i] - '0';

	int nHightestPos = add(MAXLEN, an1, an2);
	for (int i = nHightestPos; i >= 0; --i)
		printf("%d", an1[i]);

	return 0;
}


