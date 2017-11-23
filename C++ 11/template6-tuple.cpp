#include <iostream>
#include <string>

using namespace::std;

namespace myspace {
	template<typename... Values> class tuple;
	template<> class tuple<> { };

	template<typename Head, typename... Tail>
	class tuple<Head, Tail...> : private tuple<Tail...>
	{
		typedef tuple<Tail...> inherited;
	public:
		tuple(){}
		tuple(Head v, Tail... vtail)
			: m_head(v), inherited(vtail...) { }

		Head head() { return m_head; }
		//or
		//auto head()->decltype(m_head) { return m_head; }
		inherited& tail() { return *this; }
	protected:
		Head m_head;
	};
}

int main()
{
	myspace::tuple<int, float, string> t(41, 6.3, "nico");

	cout << sizeof(t) << endl; //36

	cout << t.head() << endl;
	cout << t.tail().head() << endl;
	cout << t.tail().tail().head() << endl;

	return 0;
}