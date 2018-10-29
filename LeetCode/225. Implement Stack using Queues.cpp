/*
225. Implement Stack using Queues
DescriptionHintsSubmissionsDiscussSolution
Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Example:

MyStack stack = new MyStack();

stack.push(1);
stack.push(2);  
stack.top();   // returns 2
stack.pop();   // returns 2
stack.empty(); // returns false
Notes:

You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
*/

class Stack {
public:
	queue<int> que;
	// Push element x onto stack.
	void push(int x) {
		que.push(x);
		for(int i=0;i<que.size()-1;++i){
			que.push(que.front());
			que.pop();
		}
	}

	// Removes the element on top of the stack.
	void pop() {
		que.pop();
	}

	// Get the top element.
	int top() {
		return que.front();
	}

	// Return whether the stack is empty.
	bool empty() {
		return que.empty();
	}
};




class MyStack {
private:
    queue<int> q;
public:
    void push(int x) {
        queue<int> q2;
        while (!q.empty()) {
            q2.push(q.front());
            q.pop();
        }
        q.push(x);
        while (!q2.empty()) {
            q.push(q2.front());
            q2.pop();
        }
    }
    int pop() {
        int n = q.front();
        q.pop();
        return n;
    }
    int top() { return q.front(); }
    bool empty() { return q.empty(); }
};



















#include <ctime>
#include <numeric>
#include <unordered_map>
#include <climits>
#include <cmath>
#include <cstdio>
#include <queue>
#include <iostream>

using namespace std;

class CMyStack {
public:
	queue<int> q1;
	queue<int> q2;

	void StackPush(const int &data)
	{
		if (!q1.empty())
			q1.push(data);
		else
			q2.push(data);
	}

	int StackPop()
	{
		int ret = 0;
		if (!q2.empty()) {
			int i = q2.size();
			while (i > 1) {
				q1.push(q2.front());
				q2.pop();
				--i;
			}
			ret = q2.front();
			q2.pop();
		}
		else {
			int i = q1.size();
			while (i > 1) {
				q2.push(q1.front());
				q1.pop();
				--i;
			}
			ret = q1.front();
			q1.pop();
		}
		return ret;
	}
};

int main(int argc, char *argv[]) 
{	
	CMyStack ms;
	ms.StackPush(1);
	ms.StackPush(2);
	ms.StackPush(3);
	cout << ms.StackPop() << endl;
	cout << ms.StackPop() << endl;
	cout << ms.StackPop() << endl;

	return 0;
}