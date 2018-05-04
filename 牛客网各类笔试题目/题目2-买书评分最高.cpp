#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace::std;

struct Book
{
	int stars;
	int price;
	Book(int stars, int price) :stars(stars), price(price){}
};

int getMaxStar(int nhorror, int nscifi, int amount,
	vector<Book> &horrorList,
	vector<Book> &scifiList)
{

}



void test1()
{
	//freopen("input.txt", "r", stdin);
	int nhorror = 3, nscifi = 3;
	int amount = 50;
	vector<Book> horrorList, scifiList;
	horrorList.emplace_back(5, 10);
	horrorList.emplace_back(3, 30);
	horrorList.emplace_back(6, 20);

	scifiList.emplace_back(6, 30);
	scifiList.emplace_back(4, 30);
	scifiList.emplace_back(2, 10);

	cout << getMaxStar(nhorror, nscifi, amount, horrorList, scifiList) << endl;
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}
