/*
打印
0 1 5 6 14 15 27 28
2 4 7 13 16 26 29 42
3 8 12 17 25 30 41 43
9 11 18 24 31 40 44 53
10 19 23 32 39 45 52 54
20 22 33 38 46 51 55 60
21 34 37 47 50 56 59 61
35 36 48 49 57 58 62 63
zigzag矩阵
*/
#include <iostream>

using namespace::std;

int main()
{
	while (1) {
		int n;
		cin >> n;
		int** arr = new int*[n];
		for (int i = 0; i < n; ++i)
			arr[i] = new int[n];

		int squa = n * n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int s = i + j;
				if (s < n)
					arr[i][j] = s*(s + 1) / 2 +
					(((i + j) % 2 == 0) ? j : i);
				else {
					s = (n - i - 1) + (n - j - 1);
					arr[i][j] = squa - s*(s + 1) / 2 -
						(n - (((i + j) % 2 == 0) ? j : i));
				}
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << arr[i][j] << ' ';
			}
			cout << endl;
		}
		for (int i = 0; i < n; ++i)
			delete[](int*)arr[i];
		delete[] arr;
	}

	return 0;
}