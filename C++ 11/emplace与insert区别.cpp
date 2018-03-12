#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace::std;

struct Complicated
{
	int m_year;
	double m_country;
	string m_name;

	Complicated(int year, double country, string name) :
		m_year(year), m_country(country), m_name(name)
	{
		cout << "is constructed" << endl;
	}

	Complicated(const Complicated &other) :
		m_year(other.m_year),
		m_country(other.m_country),
		m_name(other.m_name)
	{
		cout << "is Copy constructed" << endl;
	}

	Complicated(const Complicated &&other) :
		m_year(other.m_year),
		m_country(other.m_country),
		m_name(std::move(other.m_name))
	{
		cout << "is Move constructed" << endl;
	}

};

int main()
{
	map<int, Complicated> m;
	int anInt = 4;
	double aDouble = 5.0;
	string aString = "C++";

	cout << "！insert--" << endl;
	m.insert(make_pair(4, Complicated(anInt, aDouble, aString)));

	cout << "！emplace--" << endl;
	// should be easier for the optimizer  
	m.emplace(4, Complicated(anInt, aDouble, aString));

	vector<Complicated> v;


	cout << "--emplace_back--" << endl;
	v.emplace_back(anInt, aDouble, aString);
	v.clear();
	cout << "--push_back--" << endl;
	v.push_back(Complicated(anInt, aDouble, aString));
}

/*
！insert--
is constructed
is Copy constructed
is Copy constructed
！emplace--
is constructed
is Copy constructed
--push_back--
is constructed
is Copy constructed
--emplace_back--
is Copy constructed
is constructed
*/