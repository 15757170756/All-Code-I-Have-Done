#include <iostream>
#include <initializer_list>
#include <algorithm>

using namespace::std;

namespace mytemplate {
	template<typename _Tp>
	inline _Tp max(initializer_list<_Tp> _l)
	{
		return *max_element(_l.begin(), _l.end());
	}

	int maximum(int n)
	{
		return n;
	}

	template<typename... Args>
	int maximum(int n, Args... args)
	{
		return std::max(n, maximum(args...));
	}

}

int main()
{
	using mytemplate::max;
	using mytemplate::maximum;

	cout << max({ 57, 48, 60, 100, 20, 18 }) << endl;
	cout << maximum(57, 48, 60, 100, 20, 18) << endl;

	return 0;
}