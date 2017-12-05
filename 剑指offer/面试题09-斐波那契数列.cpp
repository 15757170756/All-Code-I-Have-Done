#include <iostream>
#include <cassert>

using namespace::std;

long long FibonacciRecurssive(unsigned int n)
{
	if (n <= 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return FibonacciRecurssive(n - 1) + FibonacciRecurssive(n - 2);
}

long long FibonacciIterative(unsigned int n)
{
	if (n <= 0)
		return 0;
	else if (n <= 2)
		return 1;
	long long F1, F2;
	F1 = F2 = 1;
	long long result;
	for (int i = 2; i<n; ++i) {
		result = F1 + F2;
		F1 = F2;
		F2 = result;
	}

	return result;
}

/*
使用公式
| f(n)   f(n-1) |   | 1 1 | ^(n-1)
=
| f(n-1) f(n-2) |   | 1 0 |
*/
struct Matrix2By2
{
	Matrix2By2(
		long long m00 = 0,
		long long m01 = 0,
		long long m10 = 0,
		long long m11 = 0)
		:m_00(m00), m_01(m01), m_10(m10), m_11(m11)
	{
	}

	long long m_00;
	long long m_01;
	long long m_10;
	long long m_11;
};

Matrix2By2 MatrixMultiply(
	const Matrix2By2& matrix1,
	const Matrix2By2& matrix2)
{
	return Matrix2By2(
		matrix1.m_00 * matrix2.m_00 + matrix1.m_01 * matrix2.m_10,
		matrix1.m_00 * matrix2.m_01 + matrix1.m_01 * matrix2.m_11,
		matrix1.m_10 * matrix2.m_00 + matrix1.m_11 * matrix2.m_10,
		matrix1.m_10 * matrix2.m_01 + matrix1.m_11 * matrix2.m_11);
}

Matrix2By2 MatrixPower(unsigned int n)
{
	assert(n > 0);

	Matrix2By2 matrix;
	if (n == 1)
		matrix = Matrix2By2(1, 1, 1, 0);
	else if (n % 2 == 0) {
		matrix = MatrixPower(n / 2);
		matrix = MatrixMultiply(matrix, matrix);
	}
	else if (n % 2 == 1) {
		matrix = MatrixPower((n - 1) / 2);
		matrix = MatrixMultiply(matrix, matrix);
		matrix = MatrixMultiply(matrix, Matrix2By2(1, 1, 1, 0));
	}

	return matrix;
}

long long FibonacciMatrix(unsigned int n)
{
	int result[2] = { 0, 1 };
	if (n < 2)
		return result[n];

	Matrix2By2 PowerNMinus2 = MatrixPower(n - 1);

	return PowerNMinus2.m_00;
}

int main()
{
	int n = 9;
	long long result = 0;
	result = FibonacciRecurssive(n);
	cout << result << endl;
	result = FibonacciIterative(n);
	cout << result << endl;
	result = FibonacciMatrix(n);
	cout << result << endl;

	return 0;
}