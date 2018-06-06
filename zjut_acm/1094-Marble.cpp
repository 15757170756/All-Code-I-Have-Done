/*
1094: Marble
Time Limit: 1 Sec  Memory Limit: 128 MB
Submit: 117  Solved: 50
[Submit][Status][Web Board]
Description
Ash is a marble collector and he likes to create various ornaments using his marbles.

One day, Elsh asks him to create a simple decoration for her desk. She wants a sequence of marbles consisting of at most two different colors. To make the sequence look interesting, each pair of adjacent marbles must have different colors.

Currently, Ash has R red marbles, G green marbles, and B blue marbles. Elsh wants that the resulting sequence is as long as possible. Your task is to tell us the maximum length.

Input
The input contains multiple test cases. Process to the end of file.

Each test case contains one line with there non-negative integers R, G, and B. All the integers in the input will not exceed 100.

Output
Print the answer in a single line for each case.

Sample Input
3 0 0
5 1 2
Sample Output
1
5
HINT
Source
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int r, g, b;
	while (cin >> r >> g >> b) {
		vector<int> rgb;
		rgb.push_back(r);
		rgb.push_back(g);
		rgb.push_back(b);
		sort(rgb.begin(), rgb.end());
		if (rgb[2] == 0) {
			cout << 0 << endl;
			continue;
		}
		if (rgb[1] == 0) {
			cout << 1 << endl;
			continue;
		}
		if (rgb[1] == rgb[2]) {
			cout << 2 * rgb[1] << endl;
			continue;
		}
		if (rgb[1] != rgb[2]) {
			cout << (rgb[1] * 2 + 1) << endl;
			continue;
		}
	}

	return 0;
}

//Accepted