#include "tvf.h"
void addWith(std::vector<std::vector<node> > &lhs, const std::vector<std::vector<node>> &rhs) {
	int m, n;
	m = lhs.size();
	n = lhs[0].size();
	int i, j, k;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < 4; ++k)
				lhs[i][j].tensor[k] += rhs[i][j].tensor[k];
		}
	}
	return;
}
void dividBy(std::vector<std::vector<node> > &lhs, double scale) {
	double rev_scale = 1.0 / scale;
	int m, n;
	m = lhs.size();
	n = lhs[0].size();
	int i, j, k;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < 4; ++k)
				lhs[i][j].tensor[k] *= rev_scale;
		}
	}
}
void create_ball_tensorfield(std::vector<std::vector<node> > &blf, std::vector<std::vector<std::vector<node>> > &cachedvf, bool dir) {
	std::vector<std::vector<node>> cirf(blf.size(), std::vector<node>(blf[0].size()));
	const int PART = 64;
	double stp = 2.0 * PI / PART, theta;


	double angle_stp = 360.0 / PART;
	double x, y;
	for (int i = 0; i < PART; ++i)
	{
		
		theta = -PI + i * stp;
		//x = cos(theta);
		//y = sin(theta);

		//addWith(blf, cirf);
		//int angle = round(180.0 / PI * atan(y/x));
		//if (angle < 1) angle += 180;
#ifdef CACHE_STICK_FIELD
	//	int angle = round(180.0 / PI * theta) + 180;
		int angle = 360 * i / PART;
		if (!dir) {
			if (angle >= 180) angle -= 180;
		} else{
			if (angle < 180) angle += 180;
		}
		//if (dir) angle += 180;
		addWith(blf, cachedvf[angle]);
#else
		create_stick_tensorfield(cirf, theta, 0);///!!!!
		addWith(blf, cirf);
#endif // CACHE_STICK_FIELD

		
	}
	dividBy(blf, (double)PART);
	return;
}