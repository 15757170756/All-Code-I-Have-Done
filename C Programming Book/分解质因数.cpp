#include <iostream>
#include <vector>

using namespace::std;

//递归方法,直接打印
void prim1(int m, int n)
{
	if (m > n) {
		while (m %n != 0)
			++n;
		m /= n;
		prim1(m, n);
		cout << n << " ";
	}
}

//递归方法,存在vector中
void prim3(int m, int n, vector<int>& resultVec)
{
	if (m > n) {
		while (m % n != 0)
			++n;
		m /= n;
		prim3(m, n, resultVec);
		resultVec.push_back(n);
		//cout << n << " ";
	}
}

//迭代方法
void prim2(int m, vector<int>& resultVec)
{
	int n = 2;
	while (m > n) {
		while (m %n != 0)
			++n;
		m /= n;
		resultVec.push_back(n);
	}
}

int main()
{
	int m = 12345678;
	int n = 2;

	prim1(m, n);
	cout << endl;

	vector<int> vec;
	prim2(m, vec);
	for (int e : vec)
		cout << e << ' ';
	cout << endl;

	vec.clear();
	prim3(m, n, vec);
	for (int e : vec)
		cout << e << ' ';
	cout << endl;

	return 0;
}