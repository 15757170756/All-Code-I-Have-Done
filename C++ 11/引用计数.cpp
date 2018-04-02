#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace::std;

class HasPtr
{
public:
	HasPtr(const string &s = string()) :
		ps(new string(s)), i(0), use(new size_t(1)) {}
	HasPtr(const HasPtr &p) :
		ps(p.ps), i(p.i), use(p.use) {
		++*use;
	}
	HasPtr& operator=(const HasPtr &rhs);
	~HasPtr();
private:
	string *ps;
	int i;
	size_t *use;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	++*rhs.use;
	if (0 == --*use) {
		delete ps;
		delete use;
	}
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;

	return *this;
}

HasPtr::~HasPtr()
{
	if (0 == --*use) {
		delete ps;
		delete use;
	}
}

int main(int argc, char* argv[])
{
	ifstream in("input.txt");


	return 0;
}




