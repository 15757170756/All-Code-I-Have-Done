/*
给定一个整数，按10进制来看，计算里面包含多少个0。
不能用snprint f转成字符串。 int count( int value );
*/
int count(int value)
{
	int cnt = 0;
	if (value < 0)
		value = -value;
	else if (value == 0)
		return 1;
	while (value) {
		if (value % 10 == 0)
			++cnt;
		value /= 10;
	}

	return cnt;
}

void testCount()
{
	cout << count(100) << endl;
	cout << count(101) << endl;
	cout << count(INT_MAX) << endl;
	cout << count(INT_MIN) << endl;
	cout << count(0) << endl;
	cout << count(-1001) << endl;
}
//这样写其实和转成字符串有些类似的。。。