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


char szLine1[MAXLEN], szLine2[MAXLEN];
unsigned int an1[MAXLEN], an2[MAXLEN];
unsigned int aResult[MAXLEN * 2 + 1];

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", szLine1);
		scanf("%s", szLine2);
		int i, j;
		memset(an1, 0, sizeof(an1));
		memset(an2, 0, sizeof(an2));
		memset(aResult, 0, sizeof(aResult));

		int nLen1 = strlen(szLine1);
		for (int j = 0, i = nLen1 - 1;
			i >= 0; --i)
			an1[j++] = szLine1[i] - '0';

		int nLen2 = strlen(szLine2);
		for (int j = 0, i = nLen2 - 1;
			i >= 0; --i)
			an2[j++] = szLine2[i] - '0';


		for (int i = 0; i < nLen2; ++i) {
			for (int j = 0; j < nLen1; ++j) {
				aResult[i + j] += an2[i] * an1[j];
			}
		}

		int nHighEstPos = 0;
		for (int i = 0; i < MAXLEN * 2; ++i) {
			if (aResult[i] >= 10) {
				aResult[i + 1] += aResult[i] / 10;
				aResult[i] %= 10;
			}
			if (aResult[i])
				nHighEstPos = i;
		}

		for (int i = nHighEstPos; i >= 0; --i)
			printf("%d", aResult[i]);
		printf("\n");
	}

	return 0;
}


