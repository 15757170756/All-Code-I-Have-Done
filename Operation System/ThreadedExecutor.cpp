#include <zthread/ThreadedExecutor.h>
#include <iostream>
#include "LiftOff.h"

using namespace::std;
using namespace::ZThread;

#pragma comment(lib, "ZThread.lib")

int main()
{
	try {
		ThreadedExecutor executor;
		for (int i = 0; i < 5; ++i)
			executor.execute(new LiftOff(10, i));
	}
	catch (Synchronization_Exception& e) {
		cerr << e.what() << endl;
	}


	return 0;
}