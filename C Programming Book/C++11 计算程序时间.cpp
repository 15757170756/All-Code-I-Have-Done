#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>

void f()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
	auto t1 = std::chrono::high_resolution_clock::now();
	f();
	auto t2 = std::chrono::high_resolution_clock::now();

	// integral duration: requires duration_cast
	auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	// fractional duration: no duration_cast needed
	std::chrono::duration<double, std::milli> fp_ms = t2 - t1;

	std::cout << "f() took " << fp_ms.count() << " ms, "
		<< "or " << int_ms.count() << " whole milliseconds\n";


	//or
	auto start = system_clock::now();
	//dosomething
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "花费了"
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den
		<< "秒" << endl;
}


#include <ctime>
using namespace std;

clock_t start = clock();
// do something...
clock_t end = clock();
cout << "花费了" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;


