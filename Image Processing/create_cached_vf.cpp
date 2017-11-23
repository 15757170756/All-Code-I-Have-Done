#include "tvf.h"
void create_cached_vf(std::vector<std::vector<std::vector<node>>> &cache)
{
	cache.resize(361);
	std::vector<std::vector<node>> tmpf(WS, std::vector<node>(WS));
	double theta, x, y;
	for (int i = 0; i < 180; ++i)
	{
		cache[i].resize(WS, std::vector<node>(WS));
		theta = i / 180.0 * PI;
		//normal 0-PI
		create_stick_tensorfield(tmpf, theta, 0);
		//x = cos(PI / 180 * i);
		//y = sin(PI / 180 * i);
		//create_stick_tensorfield(tmpf, x, y);
		for (int j = 0; j < WS; ++j)
			for (int k = 0; k < WS; ++k)
				cache[i][j][k] = tmpf[j][k];
	}
	for (int i = 0; i <= 180; ++i)
	{
		cache[i + 180].resize(WS, std::vector<node>(WS));
		theta = i / 180.0 * PI;
		//tangent 0-PI
		create_stick_tensorfield(tmpf, theta, 1);
		//x = cos(PI / 180 * i);
		//y = sin(PI / 180 * i);
		//create_stick_tensorfield(tmpf, x, y);
		for (int j = 0; j < WS; ++j)
			for (int k = 0; k < WS; ++k)
				cache[i + 180][j][k] = tmpf[j][k];
	}

	return; 

}