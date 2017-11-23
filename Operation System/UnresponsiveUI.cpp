#include <fstream>
#include <string>
#include <zthread/Thread.h>
#include <iostream>

using namespace::std;
using namespace::ZThread;

#pragma comment(lib, "ZThread.lib")

int main()
{
	cout << "Press <Enter> to quit:" << endl;
	ifstream file("liftOff.h");
	string line;
	while (getline(file, line)) {
		cout << line << endl;
		Thread::sleep(200);
	}
	cin.get();
	cout << "Shutting down..." << endl;

	return 0;
}