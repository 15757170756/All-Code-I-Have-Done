#include <iostream>

using namespace::std;

class A
{
public:
	int id;

	A() :id(0)
	{
		cout << "default ctor.this=" << this <<
			" id=" << id << endl;
	}
	A(int i) :id(i)
	{
		cout << "ctor.this=" << this <<
			" id=" << id << endl;
	}
	~A()
	{
		cout << "dtor.this=" << this <<
			" id=" << id << endl;
	}
};

int main()
{
	int size = 3;
	A* buf = new A[size];
	A* tmp = buf;

	cout << hex << "buf=" << buf << " tmp=" << tmp << endl;
	for (int i = 0; i < size; ++i)
		new(tmp++)A(i);

	cout << "buf=" << buf << " tmp=" << tmp << endl;

	//delete buf;//ÓÐ´íÎó
	delete[] buf;

	int* pi = new int[10];
	delete pi;//ÎÞ´íÎó

	return 0;
}
//
//default ctor.this = 00BE7104 id = 0
//default ctor.this = 00BE7108 id = 0
//default ctor.this = 00BE710C id = 0
//buf = 00BE7104 tmp = 00BE7104
//ctor.this = 00BE7104 id = 0
//ctor.this = 00BE7108 id = 1
//ctor.this = 00BE710C id = 2
//buf = 00BE7104 tmp = 00BE7110
//dtor.this = 00BE710C id = 2
//dtor.this = 00BE7108 id = 1
//dtor.this = 00BE7104 id = 0