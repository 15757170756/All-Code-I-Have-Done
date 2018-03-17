#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace::std;

int main()
{
	vector<int> vec;
	int k = 10, l = 100;
	int range = 20;
	int result;
	for (int i = 1; i < 200; ++i) {
		int temp = rand() % 10;
		int interval = l - k + 1;
		if (temp >= interval - 1)
			result = k + temp% interval;
		else {
			int times = interval / (temp + 1) + 1;
			int sum = 0;
			for (int i = 0; i < times; ++i) {
				sum += rand() % range;
			}
			result = k + sum% interval;
		}
		//result = k + temp%interval;
		cout << result << ' ';
		vec.push_back(result);
		if (i % 10 == 0)
			cout << endl;
	}
	cout << endl;
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << vec[i] << ' ';
		if ((i + 1) % 10 == 0)
			cout << endl;
	}
}


/*
51 32 63 54 61 34 99 19 75 19
34 28 51 59 58 69 59 97 16 19
66 11 54 90 50 89 81 11 11 37
47 36 56 74 99 94 69 53 24 19
89 43 33 34 16 35 35 81 53 99
65 73 50 100 28 95 13 11 53 77
23 50 100 36 88 34 39 64 16 88
95 79 36 56 76 87 94 88 93 12
41 32 10 43 60 84 77 41 55 28
41 40 49 14 51 27 24 66 50 72

10 11 11 11 11 12 13 14 16 16
16 19 19 19 19 23 24 24 27 28
28 28 32 32 33 34 34 34 34 35
35 36 36 36 37 39 40 41 41 41
43 43 47 49 50 50 50 50 51 51
51 53 53 53 54 54 55 56 56 58
59 59 60 61 63 64 65 66 66 69
69 72 73 74 75 76 77 77 79 81
81 84 87 88 88 88 89 89 90 93
94 94 95 95 97 99 99 99 100 100

后来想了一下，其实也不难，
只要想到倍数还是可以做出来的
*/