/*
Find the total area covered by two rectilinear rectangles 
in a 2D plane.

Each rectangle is defined by its bottom left corner 
and top right corner as shown in the figure.

Rectangle Area

Example:

Input: A = -3, B = 0, C = 3, D = 4, E = 0, F = -1, G = 9, H = 2
Output: 45
Note:

Assume that the total area is never beyond the 
maximum possible value of int.
*/

class Solution {
public:
	int computeArea(int A, int B, int C, int D, int E, 
		int F, int G, int H) {
		typedef long long ll;
		ll w1 = (C - A);
		ll h1 = (D - B);
		ll area1 = abs(w1*h1);
		ll w2 = (G - E);
		ll h2 = (H - F);
		ll area2 = abs(w2*h2);
		ll total_area = area1 + area2;
		

		ll A1 = max(A, E);
		ll B1 = max(B, F);
		ll C1 = min(C, G);
		ll D1 = min(D, H);
		ll w3 = (C1 - A1);
		ll h3 = (D1 - B1);
		if (A1 == E && B1 == F &&
			C1 == G && D1 == H &&
			w3 != 0 && h3 != 0)
			return area1;
		else if (A1 == A && B1 == B &&
			C1 == C && D1 == D &&
			w3 != 0 && h3 != 0)
			return area2;
		
		if (w3 <= 0 || h3 <= 0) {
			return total_area;
		}
		ll area3 = w3*h3;

		ll res = total_area - area3;
		return res;
	}
};