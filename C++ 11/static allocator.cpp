#include <iostream>
#include <vector>
#include <string>
#include <complex>

using namespace::std;

class myAllocate {
private:
	struct obj {
		struct obj* next;
	};

public:
	void* allocat(size_t size);
	void deallocat(void* deadObj, size_t size);

private:
	obj* freeStore = nullptr;
	const int CHUNK = 5;
};

void* myAllocate::allocat(size_t size)
{
	obj* p;
	if (!freeStore) {
		size_t chunk = CHUNK * size;
		freeStore = p = (obj*)malloc(chunk);

		for (int i = 0; i < CHUNK - 1; ++i) {
			p->next = (obj*)((char*)p + size);
			p = p->next;
		}
		p->next = nullptr;
	}
	p = freeStore;
	freeStore = freeStore->next;

	return p;
}

void myAllocate::deallocat(void* p, size_t size)
{
	((obj*)p)->next = freeStore;
	freeStore = (obj*)p;
}

class Foo {
public:
	long L;
	string str;
	static myAllocate myAlloc;

public:
	Foo(long l) : L(l) {}
	static void* operator new(size_t size)
	{ return myAlloc.allocat(size); }

	static void operator delete(void* pdead, size_t size)
	{
		return myAlloc.deallocat(pdead, size);
	}
};

class Goo {
public:
	complex<double> c;
	string str;
	static myAllocate myAlloc;

public:
	Goo(const complex<double>& x) : c(x) {}
	static void* operator new(size_t size)
	{ return myAlloc.allocat(size); }

	static void operator delete(void* pdead, size_t size)
	{
		return myAlloc.deallocat(pdead, size);
	}
};

myAllocate Foo::myAlloc;
myAllocate Goo::myAlloc;

int main()
{
	Foo* Foop[100];

	cout << "sizeof(Foo)= " << sizeof(Foo) << endl;

	for (int i = 0; i < 23; ++i) {
		Foop[i] = new Foo(i);
		cout << Foop[i] << ' ' << Foop[i]->L << endl;
	}

	for (int i = 0; i < 23; ++i)
		delete Foop[i];


	Goo* Goop[100];

	cout << "sizeof(Goo)= " << sizeof(Goo) << endl;

	for (int i = 0; i < 23; ++i) {
		Goop[i] = new Goo(complex<double>(i, i));
		cout << Goop[i] << ' ' << Goop[i]->c << endl;
	}

	for (int i = 0; i < 23; ++i)
		delete Goop[i];

	return 0;
}


/*
sizeof(Foo) = 32
027DD5B0 0
027DD5D0 1
027DD5F0 2
027DD610 3
027DD630 4
027DD680 5
027DD6A0 6
027DD6C0 7
027DD6E0 8
027DD700 9
027DD750 10
027DD770 11
027DD790 12
027DD7B0 13
027DD7D0 14
027DD820 15
027DD840 16
027DD860 17
027DD880 18
027DD8A0 19
027E2050 20
027E2070 21
027E2090 22
sizeof(Goo) = 48
027E2120 (0, 0)
027E2150 (1, 1)
027E2180 (2, 2)
027E21B0 (3, 3)
027E21E0 (4, 4)
027E2558 (5, 5)
027E2588 (6, 6)
027E25B8 (7, 7)
027E25E8 (8, 8)
027E2618 (9, 9)
027E2678 (10, 10)
027E26A8 (11, 11)
027E26D8 (12, 12)
027E2708 (13, 13)
027E2738 (14, 14)
027E2FA0 (15, 15)
027E2FD0 (16, 16)
027E3000 (17, 17)
027E3030 (18, 18)
027E3060 (19, 19)
027E30C0 (20, 20)
027E30F0 (21, 21)
027E3120 (22, 22)
*/