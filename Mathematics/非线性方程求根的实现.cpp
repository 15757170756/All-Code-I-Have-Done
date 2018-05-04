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
#include <deque>

using namespace::std;

class CNonLinearEqSolver
{
protected:
	double(*fun)(double);
	double epsilon0, epsilon1;
	double IVar, rVar, IVal, rVal;
	virtual double getMidVar();
public:
	CNonLinearEqSolver(double epsilon, double(*function)(double));
	double root(double lbound, double ubound);
};

double CNonLinearEqSolver::getMidVar()
{
	return (IVal + rVar) / 2.0;
}

CNonLinearEqSolver::CNonLinearEqSolver(double epsilon, double(*function)(double))
{
	epsilon0 = 0 - epsilon;
	epsilon1 = epsilon;
	fun = function;
}

double CNonLinearEqSolver::root(double lbound, double ubound)
{
	double mVar, mVal;
	IVar = lbound;
	IVal = fun(lbound);
	if (IVal <= epsilon1 && IVal >= epsilon0)
		return lbound;

	rVar = ubound;
	rVal = fun(ubound);
	if (rVal <= epsilon1 && rVal >= epsilon0)
		return ubound;

	mVar = getMidVar();
	mVal = fun(mVar);
	while (mVal < epsilon0 || mVal > epsilon1) {
		if ((mVal > 0 && IVal < 0)
			|| (mVal < 0 && IVal > 0)) {
			rVal = mVal;
			rVar = mVar;
		}
		else {
			IVal = mVal;
			IVar = mVar;
		}
		mVar = getMidVar();
		mVal = fun(mVar);
	}

	return mVar;
}

class CChordSection :public CNonLinearEqSolver
{
protected:
	virtual double getMidVar();
public:
	CChordSection(double epsilon, double(*function)(double));
};

CChordSection::CChordSection(double epsilon,
	double(*function)(double)) : CNonLinearEqSolver(epsilon, function){}

double CChordSection::getMidVar()
{
	return IVal - IVal*(rVal - IVar) / (rVal - IVal);
}

double fun1(double x)
{
	double temp;
	temp = x*x;
	return (temp*x - temp + 7.0);
}

double fun2(double x)
{
	return sin(x) - exp(x) + 0.3;
}

int main(int argc, char* argv[])
{
	CNonLinearEqSolver eq1(0.000001, fun1);
	CChordSection eq2(0.000001, fun1);
	CNonLinearEqSolver eq3(0.000001, fun2);
	cout << eq1.root(-5, -1) << endl;
	cout << eq2.root(-5, 1) << endl;
	cout << eq3.root(-5, -1) << endl;

	return 0;
}