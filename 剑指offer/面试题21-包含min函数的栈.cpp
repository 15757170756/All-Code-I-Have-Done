#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <cassert>

using namespace::std;

template <typename T>
class StackWithMin {
private:
	stack<T> m_data;
	stack<T> m_min;
public:
	void push(const T& value);
	void pop();
	const T& min() const;
};

template <typename T>
const T& StackWithMin<T>::min() const
{
	assert(m_data.size() > 0 &&
		m_min.size() > 0);

	return m_min.top();
}

template <typename T>
void StackWithMin<T>::pop()
{
	assert(m_data.size() > 0 &&
		m_min.size() > 0);

	m_data.pop();
	m_min.pop();
}

template <typename T>
void StackWithMin<T>::push(const T& value)
{
	m_data.push(value);

	if (m_min.size() == 0 ||
		value < m_min.top())
		m_min.push(value);
	else
		m_min.push(m_min.top());
}

int main()
{
	StackWithMin<int> stackMin;
	stackMin.push(3);
	stackMin.push(4);
	stackMin.push(2);
	stackMin.push(1);
	stackMin.pop();

	int minValue = stackMin.min();
	cout << minValue << endl;

	return 0;
}

