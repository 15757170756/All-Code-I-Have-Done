/*
69. Sqrt(x)
DescriptionHintsSubmissionsDiscussSolution
Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

Example 1:

Input: 4
Output: 2
Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
Seen this question in a real interview before?  

*/

class Solution {
public:
	int mySqrt(int x) {
        if(x == 0)
            return 0;
		double x1 = x;
		double x2;
		const double eps = 0.00001;
		double deltx = (x1*x1 - x) / (2*x1);
        if (deltx == 0)
			return x;
		while (abs(deltx) > eps) {
			x2 = x1 - deltx;
			x1 = x2;
			deltx = (x1*x1 - x) / (2 * x1);
		}
		return (int)x2;
	}
};
//Submission Result: Accepted 




class Solution {
public:
	int mySqrt(int x)
	{
	    long long r = x;
	    while (r*r > x)
	        r = (r + x/r) / 2;
	    return r;
	}
};
//Submission Result: Accepted 






class Solution {
public:
	int mySqrt(int x)
	{
		if (x == 0)
			return 0;
		int left = 1, right = x;
		for (;;) {
			int mid = left + (right - left) / 2;
			if (mid > x/mid) {
				right = mid - 1;
			}
			else {
				if ((mid + 1) > x/(mid + 1))
					return mid;
				left = mid + 1;
			}
		}
	}
};
//Submission Result: Accepted 







int mySqrt(int x) {
    if(x == 0 || x == 1) 
    	return x;
    int left = 0;
    int right = x;
    while(left <= right) {
        int mid = (left+right)/2;
        int sqrt = x/mid;
        if(sqrt < mid) {
            right = mid-1;
        } else if (sqrt > mid) {
            left = mid+1;
        } else { // sqrt == mid
            return mid;
        }
    }
    return right; 
    // right+1 == left, and sqrt is between left and right values, 
    //so truncate the decimal and return right
}