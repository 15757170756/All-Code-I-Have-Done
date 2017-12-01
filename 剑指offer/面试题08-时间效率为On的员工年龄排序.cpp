#include <iostream>
#include <ctime>

using namespace::std;

/*
相当于计数排序
*/
void sortAges(int ages[], int length)
{
	if (ages == nullptr || length <= 0)
		return;

	const int oldestAge = 99;
	int timeofAge[oldestAge + 1];

	for (int i = 0; i <= oldestAge; ++i)
		timeofAge[i] = 0;

	for (int i = 0; i < length; ++i) {
		int age = ages[i];
		if (age < 0 || age > oldestAge)
			throw new exception("age out of range.");
		++timeofAge[age];
	}

	int index = 0;
	for (int i = 0; i <= oldestAge; ++i)
		for (int j = 0; j < timeofAge[i]; ++j) {
			ages[index] = i;
			++index;
		}
}

int main()
{
	const int memberNum = 10000;
	int ages[memberNum];
	srand(unsigned(time(0)));
	for (int i = 0; i < memberNum; ++i) {
		ages[i] = rand() % 100;
		//cout << ages[i] << endl;
	}

	sortAges(ages, memberNum);

	return 0;
}