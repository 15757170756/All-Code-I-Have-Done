#include <iostream>
#include <list>
#include <algorithm>

using namespace::std;

class Temp
{
public:
	Temp(){ ++N; sum += N; }
	static void reset(){ N = 0; sum = 0; }
	static unsigned int getSum(){ return sum; }

private:
	static unsigned int N;
	static unsigned int sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::sum = 0;

unsigned int sumSolution1(unsigned int n)
{
	Temp::reset();
	Temp *a = new Temp[n];
	delete[] a;
	a = nullptr;

	return Temp::getSum();
}



class A;
A *array[2];

class A
{
public:
	virtual unsigned int sum(unsigned int n) { return 0; }
};

class B :public A
{
	virtual unsigned int sum(unsigned int n)
	{
		return array[!!n]->sum(n - 1) + n;
	}
};

unsigned int sumSolution2(unsigned int n)
{
	A a;
	B b;
	array[0] = &a;
	array[1] = &b;

	int value = array[1]->sum(n);
	return value;
}


typedef unsigned int(*fun)(unsigned int);

unsigned int sumSolution3Teminator(unsigned int n)
{
	return 0;
}

unsigned int sumSolution3(unsigned int n)
{
	static fun f[2] = { sumSolution3Teminator, sumSolution3 };
	return n + f[!!n](n - 1);
}


template <unsigned int n>
struct sumSolution4
{
	enum Value { N = sumSolution4<N - 1>::N + n };
};

template<>
struct sumSolution4<1>
{
	enum Value { N = 1 };
};

int main(int argc, char* argv[])
{
	int n = 50;
	cout << sumSolution1(n) << endl;
	cout << sumSolution2(n) << endl;
	cout << sumSolution3(n) << endl;
	const int constn = 50;
	//cout << sumSolution4<50>::N << endl;

	return 0;
}




