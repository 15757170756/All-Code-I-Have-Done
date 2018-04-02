/*

*/
#include <vector>
#include <iostream>

using namespace::std;

int main(int argc, char* argv[])
{
	vector<int> vec(2, 4);
	//cout << vec.data() << endl;
	//vec.reserve(10);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;

	vec.push_back(2);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;

	vec.push_back(3);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;

	vec.push_back(4);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;

	vec.push_back(5);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;

	vec.push_back(6);
	cout << vec.data() << endl;
	cout << vec.size() << ' ' << vec.capacity() << endl;

}

/*
VS2013下输出的结果
009C7530
2 2
009D1590
3 3
009CFC40
4 4
009CF528
5 6
009CF528
6 6
009CFC40
7 9
009CFC40
8 9


GUN4.8下输出的结果
0x7d2010
2 2
0x7d2030
3 4
0x7d2030
4 4
0x7d2050
5 8
0x7d2050
6 8
0x7d2050
7 8
0x7d2050
8 8
*/
