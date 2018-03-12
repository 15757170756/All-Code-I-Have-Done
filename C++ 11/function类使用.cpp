#include <iostream>
#include <functional>
using namespace std;

// 传统C函数
int c_function(int a, int b)
{
	return a + b;
}

// 函数对象
class Functor
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

int main(int argc, char** argv)
{
	int(*f)(int, int);    // 声明函数类型，赋值只能是函数指针
	f = c_function;
	cout << f(3, 4) << endl;

	Functor ff = Functor(); // 声明函数对象类型，赋值只能是函数对象
	cout << ff(3, 4) << endl;
}






#include <iostream>
#include <functional>
using namespace std;

// 传统C函数
int c_function(int a, int b)
{
	return a + b;
}

// 函数对象
class Functor
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

int main(int argc, char** argv)
{
	// 万能可调用对象类型
	std::function<int(int, int)> callableObject;

	// 可以赋值为传统C函数指针
	callableObject = c_function;
	cout << callableObject(3, 4) << endl;

	// 可以赋值为函数对象
	Functor functor;
	callableObject = functor;
	cout << callableObject(3, 4) << endl;

	// 可以赋值为lambda表达式（特殊函数对象）
	callableObject = [](int a, int b){
		return a + b;
	};
	cout << callableObject(3, 4) << endl;
}



#include <iostream>
#include <functional>
#include <list>
using namespace std;

// 传统C函数
int c_function(int a, int b)
{
	return a + b;
}

// 函数对象
class Functor
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

int main(int argc, char** argv)
{
	Functor functor;
	std::list<std::function<int(int, int)>> callables;

	callables.push_back(c_function);
	callables.push_back(functor);
	callables.push_back([](int x, int y)->int{
		return x + y;
	});

	for (const auto& e : callables)
	{
		cout << e(3, 4) << endl;
	}
}