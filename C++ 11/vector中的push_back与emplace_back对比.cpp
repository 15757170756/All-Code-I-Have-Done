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
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

using namespace::std;

class A
{
public:
	int a;
	A(int a) :a(a){ cout << "Construct\n"; }
	A(){ cout << "Construct\n"; }
	A(const A &others) : a(others.a) { cout << "Copy Construct\n"; }
};

void test1()
{
	cout << "仅调用一次push_back和emplace_back：\n";
	//A a1;
	vector<A> vec1, vec2;
	cout << "vec1 push_back test:\n";
	vec1.push_back(A(1));

	cout << "\nvec2 emplace_back test:\n";
	vec2.emplace_back(1);
}

void test2()
{
	cout << "调用多次push_back和emplace_back：\n";
	//A a1;
	vector<A> vec1, vec2;
	cout << "vec1 push_back test:\n";
	vec1.push_back(A(1));
	vec1.push_back(A(2));
	vec1.push_back(A(3));

	cout << "\nvec2 emplace_back test:\n";
	vec2.emplace_back(1);
	vec2.emplace_back(2);
	vec2.emplace_back(3);
}

int main()
{
	test1();
	cout << endl;
	test2();

	return 0;
}