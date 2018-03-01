#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

# define MAX_SIZE 100

using namespace std;

struct CountAndValue
{
	int count;
	int value;
};

int mostNumOfTimes(vector<int>& vec)
{
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << endl;

	CountAndValue pair1, pair2;
	pair1.count = 0;
	pair1.value = 0;
	pair2.count = 1;
	pair2.value = vec.front();
	for (int i = 0; i < vec.size() - 1; ++i) {
		if (vec[i] == vec[i + 1])
			++pair2.count;
		else {
			if (pair2.count > pair1.count)
				pair1 = pair2;
			pair2.count = 1;
			pair2.value = vec[i + 1];
		}
	}
	if (pair2.count > pair1.count)
		pair1 = pair2;

	return pair1.count;
}

int main()
{

	return 0;
}