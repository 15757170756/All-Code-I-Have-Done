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


}

int main()
{
	using mytemplate::max;

	cout << max({ 57, 48, 60, 100, 20, 18 }) << endl;

	return 0;
}