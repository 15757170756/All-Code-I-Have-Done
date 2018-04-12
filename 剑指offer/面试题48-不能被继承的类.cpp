#include <iostream>
#include <list>
#include <algorithm>

using namespace::std;

class A final
{

};

//error:不能将final类类型用作基类；
//class B :public A
//{
//
//};

template <typename T>
class makeSealed
{
	friend T;
private:
	makeSealed(){}
	~makeSealed(){}
};

class sealedClass2 :virtual public makeSealed<sealedClass2>
{
public:
	sealedClass2(){}
	~sealedClass2(){}
};

class Try :public sealedClass2
{
public:
	//Try(){}
	//~Try(){}
};

int main(int argc, char* argv[])
{
	//错误：
	//Try t1;

	return 0;
}




