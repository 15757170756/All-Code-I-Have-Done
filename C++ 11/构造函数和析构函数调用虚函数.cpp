https://blog.csdn.net/to_xidianhph_youth/article/details/39134801


class Base
{
public:
	Base()
	{
		Fuction();
	}

	virtual void Fuction()
	{
		cout << "Base::Fuction" << endl;
	}
};

class A : public Base
{
public:
	A()
	{
		Fuction();
	}

	virtual void Fuction()
	{
		cout << "A::Fuction" << endl;
	}
};

// 这样定义一个A的对象，会输出什么？
A a;
首先调用应该是没有问题的，但是得到的结果呢？
很多人会说输出：A::Fuction A::Function
如果是按照上面的情形进行输出的话，那就是说在构造Base的时候，也就是在Base的构造函数中调用Fuction的时候，调用了子类A的Fuction，而实际上A还没有开始构造，这样函数的行为就是完全不可预测的，因此显然不是这样，实际的输出结果是：
Base::Fuction
A::Fuction










#include <iostream>using namespace std;
class A
{
public:
	A()
	{
		cout << "A构造函数";
		Test();
	}
	~A()
	{
		cout << "A析构函数";
		cout << "A::Test()" << endl;
	}
	virtual void Test()
	{
		cout << "A::Test()" << endl;
	}
};

class B :public A
{
public:
	B()
	{
		cout << "B构造函数";
		Test();
	}
	~B()
	{
		cout << "B析构函数";
		Test();
	}
	virtual void Test()
	{
		cout << "B::Test()" << endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	A* pA = new B();    调用构造函数  输出A构造函数：A::Test() B调用构造函数B::Test()

		cout << "动态调用：";
	pA->Test();         原指针类型是PA，实际指针类型是B，由于是虚函数，所以按实际类型调用 B::Test(

		delete pA;     由于A的析构不是虚函数，所以按照原类型指针调用，如果在A的析构函数中加上virtual 则输出为B析构函数B::Test A析构函数A::Test
		return 0;
}








#include<iostream>using namespace std; 
class A
{
public:
	void virtual f()
	{
		cout << "A" << endl;
	}
};
class B : public A
{
public:
	void virtual f()
	{
		cout << "B" << endl;
	}
};
int main()
{
	A* pa = new A();
	pa->f(); 这个很明显A
		B* pb = (B*)pa;
	pb->f(); 这个强制将pa复制到pb，所以pb指向A
		delete pa, pb; 删除pa, pb所指向的地址，但是pa、pb指针并没有删除，悬浮指针
		pa = new B();
	pa->f();         B
		pb = (B*)pa;
	pb->f();         B
		return 0;
}
总结：虚函数根据指针实际类型调用，其他函数都是根据原类型调用。