#include "tvf.h"
void convert_tensor_ev(double *tensor, double *ev){
	double t, a, b, ab2;
	//trace/2
	t = (tensor[0] + tensor[3]) / 2.0;

	a = tensor[0] - t;
	b = tensor[1];
	ab2 = sqrt(a * a + b * b);
	double theta = atan2(ab2 - a, b);

	//eigen value
	ev[0] = ab2 + t;
	ev[1] = -ab2 + t;

	//eigen vector correspond to ev[0]
	ev[2] = cos(theta);
	ev[3] = sin(theta);

	//eigen vector correspond to ev[1]
	ev[4] = -sin(theta);//-sin(theta)
	ev[5] = cos(theta); //cos(theta)

	return;
}
void convert_ev_tensor(double *ev, double *tensor) {
	//ev[0] => [ev[2], ev[3]]
	//ev[1] => [ev[4], ev[5]]
	tensor[0] = ev[0] * ev[2] * ev[2] + ev[1] * ev[4] * ev[4];
	tensor[1] = ev[0] * ev[2] * ev[3] + ev[1] * ev[4] * ev[5];
	tensor[2] = tensor[1];
	tensor[3] = ev[0] * ev[3] * ev[3] + ev[1] * ev[5] * ev[5];
	return;
}