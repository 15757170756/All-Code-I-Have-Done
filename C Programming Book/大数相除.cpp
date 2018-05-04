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
int an1[MAXLEN], an2[MAXLEN];
int anResult[MAXLEN];
int tmpAn2[MAXLEN];
char szNouse[MAXLEN];

int Substract(int nMaxLen, int *an1, int *an2)
{
	int nSatrtPos = 0;
	for (int i = 0; i < nMaxLen; ++i) {
		an1[i] -= an2[i];
		if (an1[i] < 0) {
			an1[i] += 10;
			--an1[i + 1];
		}
		if (an1[i])
			nSatrtPos = i;
	}

	return nSatrtPos;
}

int Length(int nMaxLen, int *an)
{
	int i;
	for (i = nMaxLen - 1; an[i] == 0 && i >= 0; --i);
	if (i >= 0)
		return i + 1;
	return 0;
}

void shiftLeftn(int nMaxLen, int *an1, int *an2, int n)
{
	memcpy(an2, an1, nMaxLen * sizeof(int));
	if (n <= 0)
		return;
	for (int i = nMaxLen - 1; i >= 0; --i) {
		if (i - n >= 0)
			an2[i] = an1[i - n];
		else
			an2[i] = 0;
	}
}

int* Max(int nMaxLen, int *an1, int *an2)
{
	bool bBothZero = true;
	for (int i = nMaxLen - 1; i >= 0; --i) {
		if (an1[i] > an2[i])
			return an1;
		else if (an1[i] < an2[i])
			return an2;
		else if (an1[i])
			bBothZero = false;
	}

	if (bBothZero)
		return nullptr;
	return an1;
}

int main(int argc, char* argv[])
{
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	gets(szNouse);
	while (n--) {
		gets(szLine1);
		gets(szLine2);
		//gets(szNouse);
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

		int nHighEstPos = 0;
		memset(anResult, 0, sizeof(anResult));
		int nShiftLen = Length(MAXLEN, an1) - Length(MAXLEN, an2);
		while (Max(MAXLEN, an1, an2) == an1) {
			shiftLeftn(MAXLEN, an2, tmpAn2, nShiftLen);
			while (Max(MAXLEN, an1, tmpAn2) == an1) {
				Substract(MAXLEN, an1, tmpAn2);
				++anResult[nShiftLen];
			}
			if (nHighEstPos == 0 && anResult[nShiftLen])
				nHighEstPos = nShiftLen;
			--nShiftLen;
		}

		for (int i = nHighEstPos; i >= 0; --i)
			printf("%d", anResult[i]);
		printf("\n");
	}

	return 0;
}