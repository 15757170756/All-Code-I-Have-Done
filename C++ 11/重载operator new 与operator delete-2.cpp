/*
�����д���
*/

#include <iostream>
#include <complex>
#include <cstdio>
#include <string>

using namespace::std;

class Bad{};

class Foo
{
public:
	Foo() { cout << "Foo:Foo()" << endl; }
	Foo(int) { cout << "Foo::Foo(int)" << endl; throw Bad(); }

public:
	void* operator new(size_t size)
	{
		return malloc(size);
	}
		//����placement new()
		void* operator new(size_t size, void* start)
	{
		return start;
	}

		void* operator new(size_t size, long extra)
	{
		return malloc(size + extra);
	}

		void* operator new(size_t size, long extra, char init)
	{
		return malloc(size + extra);
	}

		//placement new�ĵ�һ��������Ϊsize_t
		//void* operator new(long size, long extra)
		//{
		//	return malloc(size + extra);
		//}

		//�������Ӧ��operator delete
		void operator delete(void* p, size_t size)
	{
		cout << "operator delete(void*, size_t)" << endl;
	}

	void operator delete(void* p, void*)
	{
		cout << "operator delete(void*, void*)" << endl;
	}

	void operator delete(void* p, long)
	{
		cout << "operator delete(void*, long)" << endl;
	}

	void operator delete(void* p, long, char)
	{
		cout << "operator delete(void*, long, char)" << endl;
	}

private:
	int m_i;

};


int main()
{
	Foo start;
	Foo* p1 = new Foo;
	Foo* p2 = new(&start)Foo;
	Foo* p3 = new(100)Foo;
	Foo* p4 = new(100, 'a')Foo;
	Foo* p5 = new(100)Foo(1);
	//Foo* p6 = new(100, 'a') Foo(1);
	//Foo* p7 = new(&start) Foo(1);
	//Foo* p8 = new Foo(1);

	return 0;
}
