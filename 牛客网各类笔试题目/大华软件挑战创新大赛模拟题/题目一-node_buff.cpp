/*
"node_buffer定义了一个用于存储int型数据的缓冲器，请实现其声明的所有成员方法，
并满足如下要求：
1.除非调用pop_front，否则push_back成功的数据节点不可移除；
2.不可添加给定之外的数据成员和成员方法；"

"输入的第一行指定用例数量T；
用例的第一行输入指定队列的最大节点数K；
用例的第二行输入指定插入的节点数量M；
用例的第三行输入指定插入的节点数值，使用空格隔开；
用例的第四行输入指定移除的节点数量N；"

node_buffer中剩余的节点数据值，使用空格隔开；
K > 0
Input:
1
8
9
1 2 3 4 5 6 7 8 9
4
Output:
5 6 7 8"


"class node_buffer
{
public:
// 构造函数
// 参数: max_size 指定缓冲的最大节点数
node_buffer(int max_size);

// 析构函数
~node_buffer();

// 从队尾插入一个数据节点
// 参数：i 待插入节点
// 返回值：true 插入成功
//         false 插入失败，表示数据节点个数达到最大值
bool push_back(int i);

// 从队首移除一个数据节点
// 返回值：true 移除成功
//         false 移除失败，表示数据节点个数为0
bool pop_front();

// 获取队首节点值，不移除数据
int front();

// 获取队尾节点值，不移除数据
int back();

// 获取数据节点数量
// 返回值：数据节点数量
int size();
private:
int* m_queue;
int  m_max_size;
int  m_front;
int  m_back;
int  m_size;
};

*/



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

using namespace::std;

class node_buffer
{
public:
	// 构造函数
	// 参数: max_size 指定缓冲的最大节点数
	node_buffer(int max_size)
	{
		m_max_size = max_size;
		m_queue = new int[m_max_size];
		memset(m_queue, 0, m_max_size * sizeof(int));
		m_front = m_back = m_size = 0;
	}

	// 析构函数
	~node_buffer()
	{
		if (m_queue != nullptr) {
			delete[] m_queue;
			m_queue = nullptr;
		}
	}

	// 从队尾插入一个数据节点
	// 参数：i 待插入节点
	// 返回值：true 插入成功
	//         false 插入失败，表示数据节点个数达到最大值
	bool push_back(int i)
	{
		if (m_back < m_max_size) {
			m_queue[m_back++] = i;
			m_size = m_back - m_front;
			return true;
		}
		else
			return false;

	}

	// 从队首移除一个数据节点
	// 返回值：true 移除成功
	//         false 移除失败，表示数据节点个数为0
	bool pop_front()
	{
		if (m_front < m_max_size) {
			++m_front;
			m_size = m_back - m_front;
			return true;
		}
		else
			return false;
	}

	// 获取队首节点值，不移除数据
	int front() { return m_queue[m_front]; }

	// 获取队尾节点值，不移除数据
	int back() { return m_queue[m_back]; }

	// 获取数据节点数量
	// 返回值：数据节点数量
	int size() { return m_size; }
private:
	int* m_queue;
	int  m_max_size;
	int  m_front;
	int  m_back;
	int  m_size;
};


void test1()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	while (T--) {
		int K, M;
		cin >> K >> M;
		node_buffer nodeBuffer(K);
		int temp;
		for (int i = 0; i < M; ++i) {
			cin >> temp;
			nodeBuffer.push_back(temp);
		}
		int N;
		cin >> N;
		while (N--)
			nodeBuffer.pop_front();
		while (nodeBuffer.size() > 0) {
			cout << nodeBuffer.front() << endl;
			nodeBuffer.pop_front();
		}
	}
}


int main(int argc, char* argv[])
{
	test1();

	return 0;
}











//参考答案
#include <iostream>
#include <string>
#include <list>

using namespace std;

class node_buffer
{
public:
	// 构造函数
	// 参数: max_size 指定缓冲的最大节点数
	node_buffer(int max_size);

	// 析构函数
	~node_buffer();

	// 从队尾插入一个数据节点
	// 参数：i 待插入节点
	// 返回值：true 插入成功
	//         false 插入失败，表示数据节点个数达到最大值
	bool push_back(int i);

	// 从队首移除一个数据节点
	// 返回值：true 移除成功
	//         false 移除失败，表示数据节点个数为0
	bool pop_front();

	// 获取队首节点值，不移除数据
	int front();

	// 获取队尾节点值，不移除数据
	int back();

	// 获取数据节点数量
	// 返回值：数据节点数量
	int size();
private:
	int* m_queue;
	int  m_max_size;
	int  m_front;
	int  m_back;
	int  m_size;
};

node_buffer::node_buffer(int max_size)
{
	m_front = 0;
	m_back = 0;
	m_max_size = max_size;
	m_size = 0;
	m_queue = new int[m_max_size];
}

node_buffer::~node_buffer()
{
	delete[] m_queue;
}

bool node_buffer::push_back(int i)
{
	if (m_size >= m_max_size){
		return false;
	}

	m_queue[m_back] = i;

	++m_size;
	m_back = (m_back + 1) % m_max_size;
	return true;
}

bool node_buffer::pop_front()
{
	if (m_size <= 0){
		return false;
	}
	--m_size;
	m_front = (m_front + 1) % m_max_size;
	return true;
}

int node_buffer::front()
{
	return m_queue[m_front];
}

int node_buffer::back()
{
	return m_queue[(m_back + m_max_size - 1) % m_max_size];
}

int node_buffer::size()
{
	return m_size;
}

int main(int argc, char** argv)
{
	int t;
	cin >> t;
	while (t--){
		int max_size;
		cin >> max_size;
		int count;
		cin >> count;

		node_buffer* nb = new node_buffer(max_size);
		for (int i = 0; i < count; ++i){
			int value;
			cin >> value;
			nb->push_back(value);
		}
		cin >> count;
		for (int i = 0; i < count; ++i){
			nb->pop_front();
		}

		while (nb->size()){
			if (nb->size() > 1){
				cout << nb->front() << " ";
				nb->pop_front();
			}
			else{
				cout << nb->back() << endl;
				nb->pop_front();
			}
		}

		delete nb;
	}
	return 0;
}