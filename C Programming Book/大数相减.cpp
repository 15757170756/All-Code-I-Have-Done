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

int *an1 = new int[MAXLEN];
int *an2 = new int[MAXLEN];
char szLine1[MAXLEN], szLine2[MAXLEN];

int Substract(int nMaxlen, int *an1, int *an2, bool isPositive)
{
	int nHighestPos = 0;
	for (int i = 0; i < nMaxlen; ++i) {
		an1[i] -= an2[i];
		if (an1[i] < 0) {
			an1[i] += 10;
			--an1[i + 1];
		}
		if (an1[i])
			nHighestPos = i;
	}

	return nHighestPos;
}


int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", szLine1);
		scanf("%s", szLine2);
		int i, j;
		memset(an1, 0, MAXLEN * sizeof(an1[0]));
		memset(an2, 0, MAXLEN * sizeof(an2[0]));

		int nLen1 = strlen(szLine1);
		for (int j = 0, i = nLen1 - 1;
			i >= 0; --i)
			an1[j++] = szLine1[i] - '0';

		int nLen2 = strlen(szLine2);
		for (int j = 0, i = nLen2 - 1;
			i >= 0; --i)
			an2[j++] = szLine2[i] - '0';

		bool isPositive = true;
		if (nLen1 < nLen2)
			isPositive = false;
		else if (nLen1 == nLen2) {
			for (int i = 0; i < nLen1; ++i) {
				if (szLine1[i] == szLine2[i])
					continue;
				else if (szLine1[i] > szLine2[i]) {
					isPositive = true;
					break;
				}
				else {
					isPositive = false;
					break;
				}
			}
		}
		if (isPositive == false) {
			int *temp = an1;
			an1 = an2;
			an2 = temp;
		}
		int nHightestPos = Substract(MAXLEN, an1, an2, isPositive);
		if (isPositive == false)
			printf("%c", '-');
		for (int i = nHightestPos; i >= 0; --i)
			printf("%d", an1[i]);
		printf("\n");
	}

	return 0;
}


