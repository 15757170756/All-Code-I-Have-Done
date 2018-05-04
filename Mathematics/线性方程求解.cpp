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
#include <deque>

using namespace::std;


enum {
	Gauss = 0, Jacobi = 1, Gauss_Seidel = 2
};

class CLinearEqSysSolver
{
private:
	double epsilon0, epsilon1;
	int row, column, method;
	vector<double> matrix, valVec, varVec;
	void gaussEliminate();
	void selectPivot(int curRow);
	void jacobiIterate();
	void gaussSeidelIterate();

public:
	CLinearEqSysSolver(int nVariable, int idMethod, double epsilon);
	bool addEq(vector<double> &eq);
	void clear();
	double getVarValue(int i);
};

CLinearEqSysSolver::CLinearEqSysSolver(int nVariable,
	int idMethod, double epsilon = 0)
{
	row = 0;
	column = nVariable;
	method = idMethod;
	epsilon0 = 0 - epsilon;
	epsilon1 = epsilon;
	matrix.clear();
	valVec.clear();
	varVec.clear();
}

bool CLinearEqSysSolver::addEq(vector<double> &eq)
{
	if (row == column) return false;
	if (eq.size() != column + 1) return false;
	++row;
	for (int i = 0; i < column; ++i)
		matrix.push_back(eq[i]);
	valVec.push_back(eq[column]);
	return true;
}

void CLinearEqSysSolver::clear()
{
	matrix.clear();
	valVec.clear();
	varVec.clear();
	return;
}

double CLinearEqSysSolver::getVarValue(int i)
{
	if (varVec.size() > 0) return varVec[i];
	switch (method) {
	case Gauss:
		gaussEliminate();
		break;
	case Jacobi:
		jacobiIterate();
		break;
	case Gauss_Seidel:
		gaussSeidelIterate();
		break;
	}

	return varVec[i];
}

void CLinearEqSysSolver::gaussEliminate()
{
	int curRow, selRow, eleIdx0, eleIdx1, i, j;
	double temp;
	curRow = 0;
	eleIdx0 = 0;
	while (curRow < row) {
		selectPivot(curRow);
		eleIdx1 = eleIdx0;
		for (i = curRow + 1; i < row; ++i) {
			eleIdx1 = eleIdx1 + column;
			temp = matrix[eleIdx1 + curRow] / matrix[eleIdx0 + curRow];
			for (j = curRow; j < column; ++j) {
				matrix[eleIdx1 + j] = matrix[eleIdx1 + j] -
					matrix[eleIdx0 + j] * temp;
			}
		}
	}
}



int main(int argc, char* argv[])
{


	return 0;
}