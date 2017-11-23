#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <ctime>
#include <typeinfo>

using namespace::std;

class MyString {
public:
	static size_t Dctor; //default construction
	static size_t Ctor; //construction
	static size_t Cctor; //copy construction
	static size_t CAsgn; //copy assign
	static size_t Mctor; //move construction
	static size_t MAsgn; //move assign
	static size_t Dtor;  //destruction

private:
	char* _data;
	size_t _len;
	void _init_data(const char* s)
	{
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyString() : _data(nullptr), _len(0) { ++Dctor; }

	MyString(const char* p) : _len(strlen(p))
	{
		++Ctor;
		_init_data(p);
	}

	MyString(const MyString& str) : _len(str._len)
	{
		++Cctor;
		_init_data(str._data);
	}

	MyString(MyString&& str)
		:_data(str._data), _len(str._len)
	{
		++Mctor;
		str._len = 0;
		//搬动之后，指针指向null
		str._data = nullptr;
	}

	MyString& operator=(const MyString& str)
	{
		++CAsgn;
		if (this != &str) {
			if (_data) delete _data;
			_len = str._len;
			_init_data(str._data);
		}

		return *this;
	}

	MyString& operator=(MyString&& str)
	{
		++MAsgn;
		if (this != &str) {
			if (_data) delete _data;
			_len = str._len;
			_data = str._data;
			_len = 0;
			_data = nullptr;
		}
		return *this;
	}

	virtual ~MyString(){
		++Dtor;
		if (_data)
			delete _data;
	}

	bool operator<(const MyString& rhs) const
	{
		return
			string(this->_data) < string(rhs._data);
	}

	bool operator==(const MyString& rhs) const
	{
		return
			string(this->_data) == string(rhs._data);
	}

	char* get() const { return _data; }
};

size_t MyString::Dctor = 0; //default construction
size_t MyString::Ctor = 0; //construction
size_t MyString::Cctor = 0; //copy construction
size_t MyString::CAsgn = 0; //copy assign
size_t MyString::Mctor = 0; //move construction
size_t MyString::MAsgn = 0; //move assign
size_t MyString::Dtor = 0;  //destruction



class MyStrNoMove {
public:
	static size_t Dctor; //default construction
	static size_t Ctor; //construction
	static size_t Cctor; //copy construction
	static size_t CAsgn; //copy assign
	static size_t Dtor;  //destruction

private:
	char* _data;
	size_t _len;
	void _init_data(const char* s)
	{
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyStrNoMove() : _data(nullptr), _len(0) { ++Dctor; }

	MyStrNoMove(const char* p) : _len(strlen(p))
	{
		++Ctor;
		_init_data(p);
	}

	MyStrNoMove(const MyStrNoMove& str) : _len(str._len)
	{
		++Cctor;
		_init_data(str._data);
	}

	MyStrNoMove& operator=(const MyStrNoMove& str)
	{
		++CAsgn;
		if (this != &str) {
			if (_data) delete _data;
			_len = str._len;
			_init_data(str._data);
		}

		return *this;
	}

	virtual ~MyStrNoMove(){
		++Dtor;
		delete _data;
	}

	bool operator<(const MyStrNoMove& rhs) const
	{
		return
			string(this->_data) < string(rhs._data);
	}

	bool operator==(const MyStrNoMove& rhs) const
	{
		return
			string(this->_data) == string(rhs._data);
	}

	char* get() const { return _data; }
};

size_t MyStrNoMove::Dctor = 0; //default construction
size_t MyStrNoMove::Ctor = 0; //construction
size_t MyStrNoMove::Cctor = 0; //copy construction
size_t MyStrNoMove::CAsgn = 0; //copy assign
size_t MyStrNoMove::Dtor = 0;  //destruction

namespace std {
	template<>
	struct hash<MyStrNoMove> {
		size_t operator()(const MyStrNoMove& s) const
		{
			return hash<string>()(string(s.get()));
		}
	};
}

template<typename M, typename NM>
void test_moveable(M c1, NM c2, long value)
{
	char buf[10];

	typedef typename iterator_traits<typename M::iterator>::value_type Vltype;
	clock_t timeStart = clock();
	for (long i = 0; i < value; ++i) {
		_snprintf(buf, 10, "%d", rand());
		auto ite = c1.end();
		c1.insert(ite, Vltype(buf));
	}
	cout << "construction, milli-seconds:" << (clock() - timeStart) << endl;
	cout << "size()=" << c1.size() << endl;
	out_static_data(*(c1.begin()));

	M c11(c1);
	M c12(std::move(c1));
	c11.swap(c12);


	//typedef typename iterator_traits<typename NM::iterator>::value_type NMVltype;
	//timeStart = clock();
	//for (long i = 0; i < value; ++i) {
	//	_snprintf(buf, 10, "%d", rand());
	//	auto ite = c2.end();
	//	c2.insert(ite, NMVltype(buf));
	//}
	//cout << "construction, milli-seconds:" << (clock() - timeStart) << endl;
	//cout << "size()=" << c2.size() << endl;
	//out_static_data(*(c2.begin()));

	//M c21(c2);
	//M c22(std::move(c2));
	//c21.swap(c22);
}

template<typename T>
void out_static_data(const T& myStr)
{
	cout << typeid(myStr).name() << "--" << endl;
	cout << " CCtor=" << T::Cctor
		<< " MCtor=" << T::Mctor
		<< " CAsgn=" << T::CAsgn
		<< " MAsgn=" << T::MAsgn
		<< " Dtor=" << T::Dtor
		<< " Ctor=" << T::Ctor
		<< " DCtor=" << T::Dctor
		<< endl;
}

int main()
{
	test_moveable(vector<MyString>(),
		vector<MyStrNoMove>(), 300000L);
	return 0;
}