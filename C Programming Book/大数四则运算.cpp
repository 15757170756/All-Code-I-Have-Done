
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>
#include <climits>

using namespace std;

const int maxn = 200 + 1;

class BigNum
{
public:
	BigNum();
	void init();
	BigNum operator +(const BigNum &others) const;
	BigNum operator -(const BigNum &others) const;
	BigNum operator *(const BigNum &others) const;
	BigNum operator *(int others) const;
	BigNum operator /(const BigNum &others) const;
	int& operator [](int idx);
	int operator [](int idx) const;
	void print();
	BigNum operator <<(int shift) const;
	bool operator <(const BigNum &others) const;

private:
	int num[maxn];
	int length;
	bool isNeg;
};

BigNum::BigNum()
{
	memset(num, 0, sizeof(num));
	length = 0;
	isNeg = false;
}

void BigNum::init()
{
	char tmp[100 + 1];
	cin >> tmp;
	length = strlen(tmp);
	for (int i = 0; i < length; ++i)
		num[length - i - 1] = tmp[i] - '0';
}

void BigNum::print()
{
	if (length == 0) {
		cout << 0 << endl;
		return;
	}
	if (isNeg)
		cout << '-';
	for (int i = length - 1; i >= 0; --i)
		cout << num[i];
	cout << endl;
}

bool BigNum::operator<(const BigNum &others) const
{
	if (length != others.length)
		return length < others.length;
	for (int i = length - 1; i >= 0; --i)
		if (num[i] != others[i])
			return num[i] < others[i];
}

BigNum BigNum::operator<<(int shift) const
{
	BigNum c;
	for (int i = 0; i < length; ++i)
		c[i + shift] = num[i];
	c.length = length + shift;
	return c;
}

int BigNum::operator[](int idx) const
{
	assert(idx >= 0 && idx < maxn);
	return num[idx];
}

int& BigNum::operator[](int idx)
{
	assert(idx >= 0 && idx < maxn);
	return num[idx];
}

BigNum BigNum::operator/(const BigNum &others) const
{
	assert(others.length > 0);
	BigNum c, temp = *this;
	c.length = length - others.length + 1;
	for (int i = length - others.length; i >= 0; --i) {
		BigNum d = (others << i);
		while (!(temp < d)) {
			temp = temp - d;
			c[i]++;
		}
	}
	while (c.length > 0 && c[c.length - 1] == 0)
		c.length--;
	return c;
}

BigNum BigNum::operator*(const BigNum &others) const
{
	BigNum c;
	for (int i = 0; i < others.length; ++i)
		c = c + (((*this) * others[i]) << i);
	return c;
}


BigNum BigNum::operator*(int others) const
{
	BigNum c;
	int t = 0;
	for (int i = 0; i < length || t; ++i) {
		int s = others*num[i] + t;
		c[i] = s % 10;
		t = s / 10;
		c.length++;
	}
	return c;
}

BigNum BigNum::operator-(const BigNum &others) const
{
	if (*this < others) {
		BigNum c = others - *this;
		c.isNeg = true;
		return c;
	}
	int t = 0;
	BigNum c;
	for (int i = 0; i < length; ++i) {
		int s = num[i] - others[i] - t;
		if (s < 0) {
			s += 10;
			t = 1;
		}
		else 
			t = 0;
		c[i] = s;
		c.length++;
	}
	while (c.length > 0 && c[c.length - 1] == 0)
		--c.length;
	return c;
}

BigNum BigNum::operator+(const BigNum &others) const
{
	BigNum c;
	int t = 0;
	for (int i = 0; i < length || i < others.length || t; ++i) {
		int sum = num[i] + others[i] + t;
		c[i] = sum % 10;
		t = sum / 10;
		c.length++;
	}
	return c;
}

int main()
{
	while (1) {
		BigNum a, b, c;
		char op[2];
		a.init();
		cin >> op;
		b.init();
		switch (op[0]) {
		case '+':
			c = a + b;
			break;
		case '-':
			c = a - b;
			break;
		case '*':
			c = a*b;
			break;
		case '/':
			c = a / b;
			break;
		}
		c.print();
	}

	return 0;
}