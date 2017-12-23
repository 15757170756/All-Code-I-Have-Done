#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
	// simulate expensive operation
	std::cout << "foo()" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "foo()" << std::endl;
}

void bar()
{
	// simulate expensive operation
	std::cout << "bar()" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(6));
	std::cout << "bar()" << std::endl;
}

int main()
{
	std::cout << "starting first helper...\n";
	std::thread helperfoo(foo);
	std::thread helperbar(bar);
	std::cout << "starting second helper...\n";
	//std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "waiting for helpers to finish...\n";
	helperbar.join(); //阻塞main线程
	std::cout << "done!\n";

	helperfoo.join();

}

//output
/*starting first helper...
foo()starting second helper...

waiting for helpers to finish...
bar()
停顿2秒
foo()
停顿6秒
bar()
done!
*/

/*
解释一些我对join方法的理解
std::thread helperfoo(foo)——创建新线程并且和主线程main
一起开始运行，而join方法是阻塞当前线程
（我觉得这个当前线程应该算是主线程，也就是
main线程），立马输出第一个foo()，
然后又有helperbar线程创建这里bar()的输出不一定有时候是在
starting second helper...
waiting for helpers to finish...
后面，有时候在前面，有时候在中间，这个其实是随机的，因为
创建了helperbar线程后，main线程一起运行，打印出来的结果
是随机的。
helperbar.join();阻塞main线程，运行helpfoo线程和helperbar线程，
因为foo停顿2秒，而bar停顿6秒，所以会先打印foo()，然后打印bar()，
然后返回执行main线程，打印done！
helperfoo.join();因为main线程已经执行完成，此时阻塞并无多大意义。
当然如果foo()中停顿时间长一点，如改成10秒，最后才输出foo()。

Blocks the current thread until the thread
identified by *this finishes its execution.

The completion of the thread identified
by *this synchronizes with the corresponding successful return from join().

*/

