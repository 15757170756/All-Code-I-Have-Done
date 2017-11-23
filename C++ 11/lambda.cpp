#include <iostream>
#include <cstring>
#include <typeinfo>
#include <vector>
#include <algorithm>

using namespace::std;

template<typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x + y)
{
	return x + y;
}

int main()
{
	auto I = [] {
		cout << "hello lambda" << endl;
	};

	auto l = [] {
		cout << "hello lambd" << endl;
	};

	cout << typeid(I).name() << endl;
	cout << typeid(l).name() << endl;
	I();

	double a = 3.8;
	int b = 1;
	cout << add(a, b) << endl;

	int id = 0;
	auto f = [id]() mutable {
		cout << "id:" << id << endl;
		++id;
	};
	//与下列class相类似
	class Functor {
	private:
		int id;
	public:
		void operator() ()
		{
			cout << "id:" << id << endl;
			++id;
		}
	};



	id = 42;
	f();
	f();
	f();
	Functor f1();
	cout << id << endl;

	vector<int> vi{ 5, 28, 50, 83, 70, 590 };
	int x = 30;
	int y = 100;
	vi.erase(remove_if(vi.begin(),
		vi.end(),
		[x, y](int n) {return x < n && n < y; }),
		vi.end());

	for (auto i : vi)
		cout << i << " ";
	cout << endl;
	return 0;
}