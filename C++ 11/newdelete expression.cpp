#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <string>

using namespace::std;

int main()
{
	complex<int>* pc = new complex<int>(1, 2);
	//pc->~complex();
	pc->complex<int>::complex(2, 3);//รปฮสฬโ
	cout << *pc << endl;
	operator delete(pc);
	//delete pc;
	cout << *pc << endl;

	string* pstr = new string;
	cout << "*pstr" << *pstr << endl;

	//pstr->string::string("23");
	pstr->~string();

	class A
	{
	public:
		int id;
		A(int i) :id(i)
		{
			cout << "ctor.this=" << this <<
				" id=" << id << endl;
		}
		~A()
		{
			cout << "dctor.this=" << this << endl;
		}
	};

	A* pa = new A(1);
	pa->A::A(2);
	A::A(5);
	cout << pa->id << endl;
	delete pa;
	return 0;
}

//(2, 3)
//(-572662307, -572662307)
//*pstr
//ctor.this = 00ECCF28 id = 1
//ctor.this = 00ECCF28 id = 2
//ctor.this = 00CFFAB0 id = 5
//dctor.this = 00CFFAB0
//2
//dctor.this = 00ECCF28