#include <iostream>
#include <string>

using namespace::std;

namespace myspace {
	template<typename... Values> class tup;
	template<> class tup<> { };

	template<typename Head, typename... Tail>
	class tup<Head, Tail...>
	{
		typedef tup<Tail...> composited;
	public:
		tup(){}
		tup(Head v, Tail... vtail)
			: m_tail(vtail...), m_head(v) { }

		Head head() { return m_head; }
		composited& tail() { return m_tail; }
	protected:
		Head m_head;
		composited m_tail;
	};
}

int main()
{
	myspace::tup<int, float, string> t(41, 6.3, "nico");

	cout << sizeof(t) << endl; //140

	cout << t.head() << endl;
	cout << t.tail().head() << endl;
	cout << t.tail().tail().head() << endl;

	return 0;
}