#include <iostream>
#include <stack>

using namespace::std;

template <typename T>
class CQueue
{
public:
	CQueue(){}
	~CQueue(){}
	void appendTail(const T& node);
	T deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template <typename T>
void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}

template <typename T>
T CQueue<T>::deleteHead()
{
	if (stack2.size() <= 0) {
		while (stack1.size() > 0) {
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	if (stack2.size() == 0)
		throw new exception("the queue is empty!");

	T head = stack2.top();
	stack2.pop();
	return head;
}

int main()
{
	CQueue<int> cq1;
	cq1.appendTail(1);
	cq1.appendTail(2);
	cq1.appendTail(3);

	cout << cq1.deleteHead() << endl;

	cq1.appendTail(4);
	cq1.appendTail(5);

	cout << cq1.deleteHead() << endl;

	return 0;
}





/*
leetCode 上某人的答案
*/
class Queue {
public:

	stack<int>s1;
	stack<int>s2;

	// Push element x to the back of queue.
	void push(int x) {
		s1.push(x);
	}

	// Removes the element from in front of queue.
	void pop(void) {
		peek();
		s2.pop();
	}

	// Get the front element.
	int peek(void) {
		if (s2.empty()) transit();
		return s2.top();
	}

	void transit() {
		while (!s1.empty())
		{
			int v = s1.top();
			s1.pop();
			s2.push(v);
		}
	}

	// Return whether the queue is empty.
	bool empty(void) {
		return s1.empty() && s2.empty();
	}
};