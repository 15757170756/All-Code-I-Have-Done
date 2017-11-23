#ifndef LIFTOFF_H_
#define LiftOFF_H_

#include <iostream>
#include <zthread/Runnable.h>

using namespace::std;

class LiftOff : public ZThread::Runnable{
	int countDown;
	int id;
public:
	LiftOff(int count, int ident = 0) :
		countDown(count), id(ident) {}
	~LiftOff() { cout << id << " complete" << endl; }

	void run()
	{
		while (countDown--)
			cout << id << ":" << countDown << endl;
		cout << "Liftoff!" << endl;
	}
};

#endif