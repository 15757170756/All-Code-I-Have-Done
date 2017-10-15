#include <iostream>
#include <fstream>
#include <vector>

using namespace::std;

class LeastSquare
{
public:
	LeastSquare(const vector<double> &x, const vector<double> &y)
	{
		double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
		for (int i = 0; i < x.size(); ++i) {
			t1 += x[i] * x[i];
			t2 += x[i];
			t3 += x[i] * y[i];
			t4 += y[i];
		}

		a = (x.size() * t3 - t2 * t4) / (x.size() * t1 - t2 * t2);
		b = (t1 * t4 - t2 * t3) / (x.size() * t1 - t2 * t2);
	}

	double getY(const double x) const
	{
		return a * x + b;
	}

	void print() const
	{
		cout << "y = " << a << "x + " << b << endl;
	}

private:
	double a;
	double b;
};

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "Usage: DataFile.txt" << endl;
		return -1;
	}
	else{
		vector<double> x;
		ifstream in(argv[1]);
		for (double d; in >> d;)
			x.push_back(d);

		int sz = x.size();
		vector<double> y(x.begin() + sz / 2, x.end());
		x.resize(sz / 2);
		LeastSquare ls(x, y);
		ls.print();

		cout << "Input x: \n";
		double x0;
		while (cin >> x0) {
			cout << "y = " << ls.getY(x) << endl;
			cout << "Input x:\n";
		}
	}
}