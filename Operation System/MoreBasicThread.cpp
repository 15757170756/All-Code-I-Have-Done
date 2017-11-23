#include "LiftOff.h"
#include <zthread/Thread.h>

using namespace::std;
using namespace::ZThread;

#pragma comment(lib, "ZThread.lib")

int main()
{
	const int SZ = 5;
	try {
		for (int i = 0; i < SZ; ++i)
			Thread t(new LiftOff(10, i));
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
//User thread created.
//0pollPendingThreads()
//: 1 user - thread added.
//9User thread created.
//
//Thread starting...
//10 : pollPendingThreads()
//: 981 user - thread added.
//
//0
//: 71
//User thread created.
//: Thread starting...
//82
//01::97pollPendingThreads()
//:
//1 user - thread added.
//6Thread starting...
//
//31 :
//20User thread created.
//::5pollPendingThreads()
//
//1 user - thread added.
//: 86
//9
//Thread starting...
//4 : 90
//
//4 : Waiting for LIftOff
//1::54

//0 : 请按任意键继续. . .