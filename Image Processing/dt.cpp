#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "dt.h"

/******************* DISTANCE TRANSFORM **************/
static float arg_sweep(const float* cost, float* res, int* labels,
	int w, int h, const char x, const char y)
{
#define MAX_COST 1e10
	int i, j;
	const int tx = w, ty = h;
	float* A = res;
	int* L = labels;

	const int bx = x > 0 ? 0 : tx - 1;
	const int by = y > 0 ? 0 : ty - 1;
	const int ex = x > 0 ? tx : -1;
	const int ey = y > 0 ? ty : -1;

	double t0, t1, t2, C, max_diff = 0.0;
	int l0, l1, l2;
	for (j = by; j != ey; j += y)
		for (i = bx; i != ex; i += x) {
			if (j == by) {
				t1 = MAX_COST;
				l1 = -1;
			}
			else {
				t1 = A[i + (j - y)*tx];
				l1 = L[i + (j - y)*tx];
			}
			if (i == bx) {
				t2 = MAX_COST;
				l2 = -1;
			}
			else {
				t2 = A[i - x + j*tx];
				l2 = L[i - x + j*tx];
			}
			double dt12 = abs(t1 - t2);
			C = cost[i + j*tx];

			if (dt12 > C) {  // handle degenerate case
				if (t1 < t2) {
					t0 = t1 + C;
					l0 = l1;
				}
				else {
					t0 = t2 + C;
					l0 = l2;
				}
			}
			else {
				t0 = 0.5*(t1 + t2 + sqrt(2 * C*C - dt12*dt12));
				l0 = (t1 < t2) ? l1 : l2;
			}

			if (t0 < A[i + j*tx])  {
				max_diff = __max(max_diff, A[i + j*tx] - t0);
				A[i + j*tx] = t0;
				L[i + j*tx] = l0;
			}
		}

	return max_diff;
}

float GDT(const float* cost, float* res, int* labels, int w, int h)
{
	int max_iter = 40;
	int min_change = 1;

	assert(cost && res && labels);

	const char x[4] = { -1, 1, 1, -1 };
	const char y[4] = { 1, 1, -1, -1 };
	int i = 0, end_iter = 4;
	float change = -1;
	while (++i <= end_iter) {
		change = arg_sweep(cost, res, labels, w, h, x[i % 4], y[i % 4]);
		if (change > min_change)
			end_iter = __min(max_iter, i + 3); // finish the turn
	}
	return change;
}