#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <string>

using namespace::std;

class P {
public:
	P(int a, int b)
	{
		cout << "P(int, int), a=" << a << ", b=" << b << endl;
	}

	P(initializer_list<int> initlist)
	{
		cout << "P(initializer_list<int>), values= ";
		for (auto i : initlist)
			cout << i << ' ';
		cout << endl;
	}
};

void print(initializer_list<int> vals)
{
	for (auto p = vals.begin(); p != vals.end(); ++p)
		cout << *p << endl;
}

void initializer_list_test()
{
	vector<int> v1{ 2, 5, 7, 13, 69, 83, 50 };
	vector<int> v2({ 2, 5, 7, 13, 69, 83, 50 });
	vector<int> v3;
	v3 = { 2, 5, 7, 13, 69, 83, 50 };
	v3.insert(v3.begin() + 2, { 0, 1, 2, 3, 4 });

	for (auto i : v3)
		cout << i << " ";
	cout << endl;

	cout << max({ string("Ace"), string("Stacy"), string("Sabrina"), string("Barkley") }) << endl;
	cout << min({ string("Ace"), string("Stacy"), string("Sabrina"), string("Barkley") }) << endl;
	cout << max({ 54, 16, 48, 5 }) << endl;
	cout << min({ 54, 16, 48, 5 }) << endl;
}

int main()
{
	P p(77, 5);
	P q{ 77, 5 };
	P r{ 77, 5, 42 };
	P s = { 77, 5 };

	print({ 4, 3, 5, 3, 5, });

	initializer_list_test();
	return 0;
}