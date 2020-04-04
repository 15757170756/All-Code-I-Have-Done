/*
https://leetcode-cn.com/problems/print-in-order/
1114. 按序打印
我们提供了一个类：

public class Foo {
  public void one() { print("one"); }
  public void two() { print("two"); }
  public void three() { print("three"); }
}
三个不同的线程将会共用一个 Foo 实例。

线程 A 将会调用 one() 方法
线程 B 将会调用 two() 方法
线程 C 将会调用 three() 方法
请设计修改程序，以确保 two() 方法在 one() 方法之后被执行，three() 方法在 two() 方法之后被执行。

 

示例 1:

输入: [1,2,3]
输出: "onetwothree"
解释: 
有三个线程会被异步启动。
输入 [1,2,3] 表示线程 A 将会调用 one() 方法，线程 B 将会调用 two() 方法，线程 C 将会调用 three() 方法。
正确的输出是 "onetwothree"。
示例 2:

输入: [1,3,2]
输出: "onetwothree"
解释: 
输入 [1,3,2] 表示线程 A 将会调用 one() 方法，线程 B 将会调用 three() 方法，线程 C 将会调用 two() 方法。
正确的输出是 "onetwothree"。
 

注意:

尽管输入中的数字似乎暗示了顺序，但是我们并不保证线程在操作系统中的调度顺序。

你看到的输入格式主要是为了确保测试的全面性。

通过次数22,730提交次数37,008
*/
class Foo {
private:
	int counter = 1;
	condition_variable cv1;
	condition_variable cv2;
	mutex g_mutex;
public:
	Foo() {

	}

	void first(function<void()> printFirst) {
		// 等待直至 main() 发送数据
		unique_lock<mutex> lk(g_mutex);
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		counter++;
		cv1.notify_one();
	}

	void second(function<void()> printSecond) {
		unique_lock<mutex> lk(g_mutex);
		// printSecond() outputs "second". Do not change or remove this line.
		// 阻塞当前线程，直到条件变量被唤醒
		cv1.wait(lk, [this]() {return 2 == counter; });
		printSecond();
		counter++;
		cv2.notify_one();
	}

	void third(function<void()> printThird) {
		unique_lock<mutex> lk(g_mutex);
		cv2.wait(lk, [this]() {return 3 == counter; });
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
	}
};

/*
执行结果：
通过
显示详情
执行用时 :
124 ms
, 在所有 C++ 提交中击败了
79.00%
的用户
内存消耗 :
7.3 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
炫耀一下:
*/



class Foo {
private:
	mutex m2, m3;
public:
	Foo() {
		m2.lock();
		m3.lock();
	}

	void first(function<void()> printFirst) {	
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		m2.unlock();
	}

	void second(function<void()> printSecond) {
		// printSecond() outputs "second". Do not change or remove this line.
		m2.lock();
		printSecond();
		m3.unlock();
	}

	void third(function<void()> printThird) {

		// printThird() outputs "third". Do not change or remove this line.
		m3.lock();
		printThird();
		m3.unlock();
	}
};

/*
显示详情
执行用时 :
80 ms
, 在所有 C++ 提交中击败了
95.83%
的用户
内存消耗 :
7.2 MB
, 在所有 C++ 提交中击败了
100.00%
的用户
炫耀一下:
*/







#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <functional>


using namespace std;

class Foo {
private:
	int counter = 1;
	condition_variable cv1;
	condition_variable cv2;
	mutex g_mutex;
public:
	Foo() {

	}

	void first(function<void()> printFirst) {
		// 等待直至 main() 发送数据
		unique_lock<mutex> lk(g_mutex);
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		counter++;
		cv1.notify_one();
	}

	void second(function<void()> printSecond) {
		unique_lock<mutex> lk(g_mutex);
		// printSecond() outputs "second". Do not change or remove this line.
		// 阻塞当前线程，直到条件变量被唤醒
		cv1.wait(lk, [this]() {return 2 == counter; });
		printSecond();
		counter++;
		cv2.notify_one();
	}

	void third(function<void()> printThird) {
		unique_lock<mutex> lk(g_mutex);
		cv2.wait(lk, [this]() {return 3 == counter; });
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
	}
};



int main()
{
	int a, b, c;
	while (cin >> a >> b >> c) {
		Foo fo;
		function<void()> funcs[3];
		funcs[0] = bind(&Foo::first, &fo, []() {
			cout << "one";
		});
		funcs[1] = bind(&Foo::second, &fo, []() {
			cout << "two";
		});
		funcs[2] = bind(&Foo::third, &fo, []() {
			cout << "three";
		});
		thread t1(funcs[a - 1]);
		thread t2(funcs[b - 1]);
		thread t3(funcs[c - 1]);
		t1.join(), t2.join(), t3.join();
		cout << endl;
	}
	
}