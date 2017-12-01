#include <queue>
#include <iostream>

using namespace::std;

template <typename T>
class CStack
{
public:
	void appendTail(const T& node);
	T deleteHead();

private:
	queue<T> queue1;
	queue<T> queue2;
	T topValue;
};

template <typename T>
void CStack<T>::appendTail(const T& node)
{
	if (!queue1.empty())
		queue1.push(node);
	else
		queue2.push(node);
	topValue = node;
}

template <typename T>
T CStack<T>::deleteHead()
{
	if (!queue1.empty()) {
		T returnData;
		while (!queue1.empty()) {
			T& data = queue1.front();
			if (queue1.size() == 1)
				returnData = data;
			if (queue1.size() > 1)
				queue2.push(data);
			if (queue1.size() == 2)
				topValue = data;
			queue1.pop();
		}
		return returnData;
	}
	else {
		T returnData;
		while (!queue2.empty()) {
			T& data = queue2.front();
			if (queue2.size() == 1)
				returnData = data;
			if (queue2.size() > 1)
				queue1.push(data);
			if (queue2.size() == 2)
				topValue = data;
			queue2.pop();
		}
		return returnData;
	}
}

int main()
{
	CStack<int> stack1;
	stack1.appendTail(1);
	stack1.appendTail(2);
	stack1.appendTail(3);

	cout << stack1.deleteHead() << endl;
	cout << stack1.deleteHead() << endl;

	stack1.appendTail(4);
	stack1.appendTail(5);

	cout << stack1.deleteHead() << endl;
	cout << stack1.deleteHead() << endl;
	cout << stack1.deleteHead() << endl;
	//cout << stack1.deleteHead() << endl;

	return 0;
}