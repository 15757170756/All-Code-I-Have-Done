/*
判断整数是否是对称数，如3，123,121,12321。不能把整数转为字符串来判断。
//返回 1：对称，0：不对称 
*/
int ismirror(int value)
{
	vector<int> vec;
	while (value) {
		int temp = value % 10;
		vec.emplace_back(temp);
		value = value / 10;
	}
	for (int i = 0, j = vec.size() - 1;
		i < vec.size() / 2; ++i, --j) {
		if (vec[i] != vec[j])
			return 0;
	}
	return 1;
}

int ismirror2(int value)
{
	int reverseValue = 0, n = value;
	while (n) {
		reverseValue = reverseValue * 10 + n % 10;
		n /= 10;
	}
	if (reverseValue == value)
		return 1;
	else
		return 0;
}

void testIsMirror()
{
	cout << ismirror(123) << endl;
	cout << ismirror(1212) << endl;
	cout << ismirror(121) << endl;
	cout << ismirror(0) << endl;
	cout << ismirror(12221) << endl;
	cout << endl;

	cout << ismirror2(123) << endl;
	cout << ismirror2(1212) << endl;
	cout << ismirror2(121) << endl;
	cout << ismirror2(0) << endl;
	cout << ismirror2(12221) << endl;
}
/*
但是这样做和转化成字符串没什么不一样
面试官不满意，问还有什么想法吗。
当时居然没有想起来第二种方法，但是怎么感觉
第二种方法也有些类似第一种呀，反正都要反转一下。
*/