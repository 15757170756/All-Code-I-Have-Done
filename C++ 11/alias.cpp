#include <vector>
#include <string>
#include <list>
#include <deque>
#include <algorithm>

using namespace::std;

//template <typename T>
//using Vec = std::vector<T, MyAlloc<T>>;
//
//Vec<int> coll;
////is equivalent
//std::vector<int, MyAlloc<int>> coll;

//使用macro无法达到相同效果
//#define Vec<T> template<typename T> std::vector<T, MyAlloc<T>>;

template<typename T>
void output_static_data(const T& obj)
{
	cout << ...//static data of obj
}


template<typename Containter>
void test_moveable(Containter c)
{
	typedef typename iterator_traits<typename Containter::iterator>::value_type Valtype;

	for (long i = 0; i < SIZE; ++i)
		c.insert(c.end(), Valtype());

	output_static_data(*(c.begin()));
	Containter c1(c);
	Containter c2(std::move(c));
	c1.swap(c2);
}


template<typename T>
using Vec = vector<T, allocator<T>>;

template<typename T>
using Lst = list<T, allocator<T>>;

template<typename T>
using Deq = deque<T, allocator<T>>;

template<typename T, template<class> class Container>
class XCls {
	Container<T> c;
public:
	XCls()
	{
		for (long i = 0; i < SIZE; ++i)
			c.insert(c.end(), T());

		output_static_data(T());
		Containter<T> c1(c);
		Containter<T> c2(std::move(c));
		c1.swap(c2);
	}
};

using func = void (*)(int, int);

int main()
{
	XCls<string, Vec> c1;
	return 0;
}
