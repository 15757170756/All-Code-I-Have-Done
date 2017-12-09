#include <iostream>
#include <complex>
#include <cstdio>
#include <string>

using namespace::std;

void* myAlloc(size_t size) { return malloc(size); }

void myFree(void* ptr) { return free(ptr); }

//inline void* operator new(size_t size)
//{ 
//	cout << "licf global new() \n";
//	return myAlloc(size);
//}
//
//inline void* operator new[](size_t size)
//{
//	cout << "licf global new[]() \n";
//	return myAlloc(size);
//}
//
//inline void operator delete(void* ptr)
//{
//	cout << "licf global delete() \n";
//	myFree(ptr);
//}
//
//inline void operator delete[](void* ptr)
//{
//	cout << "licf global delete[]() \n";
//	myFree(ptr);
//}

class Foo
{
public:
	int _id;
	long data;
	string _str;

public:
	Foo() :_id(0)
	{
		cout << "default ctor.this=" <<
			this << " id=" << _id << endl;
	}

	Foo(int i) :_id(i)
	{
		cout << "ctor.this=" <<
			this << " id=" << _id << endl;
	}

	~Foo()
	{
		cout << "dtor.this=" <<
			this << " id=" << _id << endl;
	}

public:
	static void* operator new(size_t);
	static void* operator new[](size_t);

	static void operator delete(void*, size_t);
	static void operator delete[](void*, size_t);
};

void* Foo::operator new(size_t size)
{
	Foo* p = (Foo*)malloc(size);
	cout << "operator new\n";
	return p;
}

void* Foo::operator new[](size_t size)
{
	Foo* p = (Foo*)malloc(size);
	cout << "operator new[]\n";
	return p;
}

void Foo::operator delete(void* pdead, size_t size)
{
	cout << "operator delete\n";
	free(pdead);
}

void Foo::operator delete[](void* pdead, size_t size)
{
	cout << "operator delete[]\n";
	free(pdead);
}

int main()
{
	cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
	Foo* p = new Foo(7);
	delete p;

	Foo* pArray = new Foo[5];
	delete[] pArray;

	cout << endl << endl;
	//调用全局new与delete
	Foo* pGlobalNew = ::new Foo(7);
	::delete pGlobalNew;

	Foo* pArrayGlobalNew = ::new Foo[5];
	::delete[] pArrayGlobalNew;

	return 0;
}


//sizeof(Foo) = 36
//operator new
//ctor.this = 0119E3B0 id = 7
//dtor.this = 0119E3B0 id = 7
//operator delete
//operator new[]
//default ctor.this = 011A223C id = 0
//default ctor.this = 011A2260 id = 0
//default ctor.this = 011A2284 id = 0
//default ctor.this = 011A22A8 id = 0
//default ctor.this = 011A22CC id = 0
//dtor.this = 011A22CC id = 0
//dtor.this = 011A22A8 id = 0
//dtor.this = 011A2284 id = 0
//dtor.this = 011A2260 id = 0
//dtor.this = 011A223C id = 0
//operator delete[]
//
//
//ctor.this = 0119E8B0 id = 7
//dtor.this = 0119E8B0 id = 7
//default ctor.this = 011A223C id = 0
//default ctor.this = 011A2260 id = 0
//default ctor.this = 011A2284 id = 0
//default ctor.this = 011A22A8 id = 0
//default ctor.this = 011A22CC id = 0
//dtor.this = 011A22CC id = 0
//dtor.this = 011A22A8 id = 0
//dtor.this = 011A2284 id = 0
//dtor.this = 011A2260 id = 0
//dtor.this = 011A223C id = 0