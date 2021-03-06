#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace::std;

int g_maxValue = 6;

void Probablity(int original, int current,
	int sum, int *pProbabilitise)
{
	if (current == 1)
		pProbabilitise[sum - original]++;
	else
		for (int i = 1; i <= g_maxValue; ++i)
			Probablity(original, current - 1, i + sum, pProbabilitise);
}

void Probablity(int number, int *pProbabilitise)
{
	for (int i = 1; i <= g_maxValue; ++i) {
		Probablity(number, number, i, pProbabilitise);
	}
}

void printProbability(int number)
{
	if (number < 1)
		return;
	int maxSum = number * g_maxValue;
	int *pProbabilities = new int[maxSum - number + 1];
	for (int i = number; i <= maxSum; ++i) {
		pProbabilities[i - number] = 0;
	}

	Probablity(number, pProbabilities);

	int total = pow((double)g_maxValue, number);
	//double sum = 0;
	for (int i = number; i <= maxSum; ++i) {
		double ratio = (double)pProbabilities[i - number] / total;
		//sum += ratio;
		printf("%d:\t%d\t%e\n", i, pProbabilities[i - number], ratio);
	}
	//cout << sum << endl;

	delete[] pProbabilities;
}

void printProbability2(int number)
{
	if (number < 1)
		return;

	int *pProbabilities[2];
	pProbabilities[0] = new int[g_maxValue * number + 1];
	pProbabilities[1] = new int[g_maxValue * number + 1];
	for (int i = 0; i < g_maxValue * number + 1; ++i) {
		pProbabilities[0][i] = 0;
		pProbabilities[1][i] = 0;
	}
	int flag = 0;
	for (int i = 1; i <= g_maxValue; ++i)
		pProbabilities[flag][i] = 1;

	for (int k = 2; k <= number; ++k) {
		for (int i = 0; i < k; ++i)
			pProbabilities[1 - flag][i] = 0;

		for (int i = k; i <= g_maxValue * k; ++i) {
			pProbabilities[1 - flag][i] = 0;
			for (int j = 1; j <= i && j <= g_maxValue; ++j)
				pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
		}
		flag = 1 - flag;
	}

	double total = pow((double)g_maxValue, number);
	for (int i = number; i <= g_maxValue*number; ++i) {
		double ratio = (double)pProbabilities[flag][i] / total;
		printf("%d: %e\n", i, ratio);
	}

	delete[] pProbabilities[0];
	delete[] pProbabilities[1];
}



int main(int argc, char* argv[])
{
	int n = 11;
	//printProbability(n);
	printProbability2(n);
	return 0;
}




