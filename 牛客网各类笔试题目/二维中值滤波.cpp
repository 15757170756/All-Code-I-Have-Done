#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdlib>

using namespace::std;

typedef unsigned char uchar;

uchar getMedian1(uchar *arr, int n)
{
	const int charRange = 256;
	uchar count[charRange];
	uchar *result = new uchar[n];
	for (int i = 0; i < charRange; ++i)
		count[i] = 0;

	for (int i = 0; i < n; ++i)
		++count[arr[i]];

	for (int i = 0; i < charRange - 1; ++i)
		count[i + 1] += count[i];

	for (int i = 0; i < n; ++i) {
		result[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}

	if (n % 2 == 1) {
		return result[n / 2];
	}
	else {
		return (result[n / 2 - 1] + result[n / 2]) / 2;
	}
}

uchar getMedian2(uchar *arr, int n)
{
	uchar *tmp = new uchar[n];
	for (int i = 0; i < n; ++i)
		tmp[i] = arr[i];
	for (uchar i = 0; i < n - 1; ++i) {
		for (uchar j = 0; j < n - i - 1; ++j) {
			if (tmp[j] > tmp[j + 1]) {
				uchar temp = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = temp;
			}
		}
	}

	uchar mod2 = tmp[n / 2];
	uchar notMod2 = (tmp[n / 2 - 1] + tmp[n / 2]) / 2;
	delete[] tmp;
	if (n % 2 == 1)
		return mod2;
	else
		return notMod2;
}

void medianFilter1D(uchar *f, uchar *g, int H)
{
	uchar radius = 2;
	uchar L = 2 * radius + 1;

	for (int i = 0; i < H; ++i) {
		if (i - radius < 0 || i + radius >= H)
			g[i] = f[i];
		else {
			g[i] = getMedian2(f + i - radius, L);
		}
	}
}


void medianFilter2D(uchar **f, uchar **g, int H, int W)
{
	uchar radius = 1;
	uchar L = 2 * radius + 1;

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j)
			if (i - radius < 0 || i + radius >= H
				|| j - radius < 0 || j + radius >= W)
				g[i][j] = f[i][j];
			else {
				uchar *temp = new uchar[L*L];
				uchar k = 0;
				for (int m = i - radius; m <= i + radius; ++m) {
					for (int n = j - radius; n <= j + radius; ++n)
						temp[k++] = f[m][n];
				}
				g[i][j] = getMedian2(temp, L*L);
			}
	}
}

void testMedianFilter1D()
{
	const int H = 1000;
	const int charRange = 256;
	uchar *f = new uchar[H];
	uchar *g = new uchar[H];
	for (int i = 0; i < H; ++i) {
		f[i] = rand() % charRange;
	}
	medianFilter1D(f, g, H);
	for (int i = 0; i < 20; ++i)
		printf("%d ", f[i]);

	printf("\n");

	for (int i = 0; i < 20; ++i)
		printf("%d ", g[i]);
}


void testMedianFilter2D()
{
	const int H = 1000;
	const int W = 1500;
	const int charRange = 256;

	uchar **f = new uchar*[H];
	for (int i = 0; i < H; ++i)
		f[i] = new uchar[W];

	uchar **g = new uchar*[H];
	for (int i = 0; i < H; ++i)
		g[i] = new uchar[W];

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j)
			f[i][j] = rand() % charRange;
	}
	medianFilter2D(f, g, H, W);
	int testRange = 10;
	for (int i = 0; i < testRange; ++i) {
		for (int j = 0; j < testRange; ++j) {
			printf("%d ", f[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");

	for (int i = 0; i < testRange; ++i) {
		for (int j = 0; j < testRange; ++j) {
			printf("%d ", g[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	testMedianFilter1D();
	printf("\n\n");
	testMedianFilter2D();

	return 0;
}
