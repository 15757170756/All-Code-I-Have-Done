#include <chrono>   
using namespace std;
using namespace chrono;

auto start = system_clock::now();
// do something...
auto end = system_clock::now();
auto duration = duration_cast<microseconds>(end - start);
cout << "花费了"
<< double(duration.count()) * microseconds::period::num / microseconds::period::den
<< "秒" << endl;


#include <ctime>
using namespace std;

clock_t start = clock();
// do something...
clock_t end = clock();
cout << "花费了" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;