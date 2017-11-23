#include <iostream>

using namespace::std;

namespace MyTemplate {
	void printf(const char* s)
	{
		while (*s) {
			if (*s == '%' && *(++s) != '%') {
				throw runtime_error("invalid format string; missing arguments");
			}
			cout << *s++;
		}
	}

	template<typename T, typename... Args>
	void printf(const char* s, T value, Args... args)
	{
		while (*s) {
			if (*s == '%' && *(++s) != '%') {
				cout << value;
				printf(++s, args...);
				return;
			}
			cout << *s++;
		}

		throw logic_error("extra arguments provided to printf");
	}
}


int main()
{
	using MyTemplate::printf;
	int* pi = new int();
	printf("%d %s %p %f\n",
		15,
		"This is Ace",
		pi,
		3.1415926);

	return 0;
}