#include <iostream>
#include <functional>
using namespace std;

// ��ͳC����
int c_function(int a, int b)
{
	return a + b;
}

// ��������
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
	int(*f)(int, int);    // �����������ͣ���ֵֻ���Ǻ���ָ��
	f = c_function;
	cout << f(3, 4) << endl;

	Functor ff = Functor(); // ���������������ͣ���ֵֻ���Ǻ�������
	cout << ff(3, 4) << endl;
}






#include <iostream>
#include <functional>
using namespace std;

// ��ͳC����
int c_function(int a, int b)
{
	return a + b;
}

// ��������
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
	// ���ܿɵ��ö�������
	std::function<int(int, int)> callableObject;

	// ���Ը�ֵΪ��ͳC����ָ��
	callableObject = c_function;
	cout << callableObject(3, 4) << endl;

	// ���Ը�ֵΪ��������
	Functor functor;
	callableObject = functor;
	cout << callableObject(3, 4) << endl;

	// ���Ը�ֵΪlambda���ʽ�����⺯������
	callableObject = [](int a, int b){
		return a + b;
	};
	cout << callableObject(3, 4) << endl;
}



#include <iostream>
#include <functional>
#include <list>
using namespace std;

// ��ͳC����
int c_function(int a, int b)
{
	return a + b;
}

// ��������
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