/*
https://www.cnblogs.com/jerry19880126/p/3616999.html
*/

/*
先选择左侧的C/C++->命令行，
然后在其他选项这里写上/d1 reportAllClassLayout，
它可以看到所有相关类的内存布局
*/

#include <iostream>

using namespace::std;

class Base
{
	int a;
	int b;
public:
	Base(int a, int b) :a(a), b(b){}
	void commonFunction();
	virtual void VirtualFunction();
};

class DerivedClass : public Base
{
	int c;
public:
	void DerivedCommonFunction();
	void virtual VirtualFunction();
};

class DerivedClass1 : public Base
{
	int c;
public:
	void DerivedCommonFunction();
	void virtual VirtualFunction();
	//void virtual VirtualFunction2();
};

class DerivedClass2 : public Base
{
	int d;
public:
	void DerivedCommonFunction();
	void virtual VirtualFunction();
};

class DerivedDerivedClass : public DerivedClass1, public DerivedClass2
{
	int e;
public:
	void DerivedDerivedCommonFunction();
	void virtual VirtualFunction();
};


#if 0

//虚继承
class DerivedClass1 : virtual public Base
{
	int c;
public:
	void DerivedCommonFunction();
	void virtual VirtualFunction();
};

class DerivedClass2 : virtual public Base
{
	int d;
public:
	void DerivedCommonFunction();
	void virtual VirtualFunction();
};

class DerivedDerivedClass : public DerivedClass1, public DerivedClass2
{
	int e;
public:
	void DerivedDerivedCommonFunction();
	void virtual VirtualFunction();
};

#endif
int main(int argc, char* argv[])
{
	//Base b(1,2);

	return 0;
}





