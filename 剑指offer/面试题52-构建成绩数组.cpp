#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>

using namespace::std;

void multiply(const vector<int> &inputVec, vector<int> &outputVet)
{
	int len1 = inputVec.size();
	int len2 = outputVet.size();

	if (len1 == len2 && len2 > 1) {
		outputVet[0] = 1;

		for (int i = 1; i < len1; ++i)
			outputVet[i] = outputVet[i - 1] * inputVec[i - 1];

		int temp = 1;
		for (int i = len1 - 2; i >= 0; --i) {
			temp *= inputVec[i + 1];
			outputVet[i] *= temp;
		}
	}
}

int main(int argc, char* argv[])
{
	vector<int> in = { 2, 5, 4, 1, 4 };
	vector<int> out(in.size());
	multiply(in, out);
	for (int e : out)
		cout << e << ' ';
	cout << endl;

	return 0;
}