#include <iostream>
#include <complex>
#include <cstdio>
#include <string>

using namespace::std;

class Screen
{
public:
	Screen(int x) : i(x) {}
	int get() { return i; }

	static void* operator new(size_t size);
	static void operator delete(void* ptr, size_t size);

private:
	Screen* next;
	static Screen* freeStore;
	static const int screenChunk;

private:
	int i;
};

Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size)
{
	Screen* p;
	if (!freeStore) {
		//linked list 空， 申请一大块
		size_t chunk = screenChunk * size;
		freeStore = p =
			reinterpret_cast<Screen*>(new char[chunk]);
		for (; p != &freeStore[screenChunk - 1]; ++p)
			p->next = p + 1;
		p->next = 0;
	}

	p = freeStore;
	freeStore = freeStore->next;
	return p;
}

void Screen::operator delete(void* ptr, size_t size)
{
	//将delete object插回free list前端
	(static_cast<Screen*>(ptr))->next = freeStore;
	freeStore = static_cast<Screen*>(ptr);
}

int main()
{
	cout << sizeof(Screen) << endl;

	size_t const N = 100;
	Screen* p1[N];
	for (int i = 0; i < N; ++i)
		p1[i] = new Screen(i);

	for (int i = 0; i < 10; ++i)
		cout << hex << p1[i] << dec << endl;

	for (int i = 0; i < N; ++i)
		delete p1[i];

	cout << endl << endl;

	Screen* pGlobal[N];
	for (int i = 0; i < N; ++i)
		pGlobal[i] = ::new Screen(i);

	for (int i = 0; i < 10; ++i)
		cout << hex << pGlobal[i] << dec << endl;

	for (int i = 0; i < N; ++i)
		::delete pGlobal[i];

	return 0;
}



//8
//0015D578
//0015D580
//0015D588
//0015D590
//0015D598
//0015D5A0
//0015D5A8
//0015D5B0
//0015D5B8
//0015D5C0
//
//
//0015C978
//0015C8D0
//0015C6D8
//0015C908
//0015C748
//0015C9B0
//0015C940
//0015C630
//0015C780
//00162200