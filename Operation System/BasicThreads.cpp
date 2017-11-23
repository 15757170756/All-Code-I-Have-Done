#include "LiftOff.h"
#include <zthread/Thread.h>

using namespace::std;
using namespace::ZThread;

#pragma comment(lib, "ZThread.lib")

int main()
{
	try {
		Thread t(new LiftOff(10));
		cout << "Waiting for LiftOff" << endl;
	}
	catch (Synchronization_Exception &e) {
		cerr << e.what() << endl;
	}
}


//ThreadQueue created
//User thread created.
//Reference thread created.
//1 reference - thread added.
//pollPendingThreads()
//1 user - thread added.
//Thread starting...
//Waiting for LiftOff0
//:9请按任意键继续. . .
