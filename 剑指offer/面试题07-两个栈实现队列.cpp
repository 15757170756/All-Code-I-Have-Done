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
	cout << cq1.deleteHead() << endl;
	cout << cq1.deleteHead() << endl;
	cout << cq1.deleteHead() << endl;

	return 0;
}