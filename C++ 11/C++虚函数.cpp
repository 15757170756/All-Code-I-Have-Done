/*
http://blog.csdn.net/haoel/article/details/1948051/

http://blog.csdn.net/castle_kao/article/details/71024411
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace::std;

class Base {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
	virtual void h() { cout << "Base::h" << endl; }
};

class Derive : public Base
{
public:
	virtual void f() { cout << "Derive::f1" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }
	virtual void h1() { cout << "Derive::h1" << endl; }
};

int main()
{
	typedef void(*Fun)(void);
	Base b;
	Fun pFun = nullptr;

	cout << "虚函数表地址1：" << (&b) << endl;
	cout << "虚函数表地址2：" << (int*)(&b) << endl;
	cout << "虚函数表--第一个函数地址1：" << *(int*)(&b) << endl;
	cout << "虚函数表--第一个函数地址2：" << (int*)*(int*)(&b) << endl;

	pFun = (Fun)*((int*)*(int*)(&b));
	pFun();

	pFun = (Fun)*((int*)*(int*)(&b) + 0);  // Base::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&b) + 1);  // Base::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&b) + 2);  // Base::h()
	pFun();


	Derive d;
	pFun = (Fun)*((int*)*(int*)(&d) + 0);  // Base::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 1);  // Base::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 2);  // Base::h()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 3);  // Derive::g1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 4);  // Derive::h1()
	pFun();

	Base *pb = new Derive();
	pb->f();
}

/*
虚函数表地址1：004FF9E4
虚函数表地址2：004FF9E4
虚函数表--第一个函数地址1：14080784
虚函数表--第一个函数地址2：00D6DB10
Base::f
请按任意键继续. . .
*/












#include <iostream>

using namespace std;



class Base1 {

public:

	virtual void f() { cout << "Base1::f" << endl; }

	virtual void g() { cout << "Base1::g" << endl; }

	virtual void h() { cout << "Base1::h" << endl; }



};



class Base2 {

public:

	virtual void f() { cout << "Base2::f" << endl; }

	virtual void g() { cout << "Base2::g" << endl; }

	virtual void h() { cout << "Base2::h" << endl; }

};



class Base3 {

public:

	virtual void f() { cout << "Base3::f" << endl; }

	virtual void g() { cout << "Base3::g" << endl; }

	virtual void h() { cout << "Base3::h" << endl; }

};





class Derive : public Base1, public Base2, public Base3 {

public:

	virtual void f() { cout << "Derive::f" << endl; }

	virtual void g1() { cout << "Derive::g1" << endl; }

};





typedef void(*Fun)(void);



int main()

{

	Fun pFun = NULL;



	Derive d;

	int** pVtab = (int**)&d;



	//Base1's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);

	pFun = (Fun)pVtab[0][0];

	pFun();



	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);

	pFun = (Fun)pVtab[0][1];

	pFun();



	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);

	pFun = (Fun)pVtab[0][2];

	pFun();



	//Derive's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);

	pFun = (Fun)pVtab[0][3];

	pFun();



	//The tail of the vtable

	pFun = (Fun)pVtab[0][4];

	cout << pFun << endl;





	//Base2's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);

	pFun = (Fun)pVtab[1][0];

	pFun();



	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);

	pFun = (Fun)pVtab[1][1];

	pFun();



	pFun = (Fun)pVtab[1][2];

	pFun();



	//The tail of the vtable

	pFun = (Fun)pVtab[1][3];

	cout << pFun << endl;







	//Base3's vtable

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);

	pFun = (Fun)pVtab[2][0];

	pFun();



	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);

	pFun = (Fun)pVtab[2][1];

	pFun();



	pFun = (Fun)pVtab[2][2];

	pFun();



	//The tail of the vtable

	pFun = (Fun)pVtab[2][3];

	cout << pFun << endl;



	return 0;

}