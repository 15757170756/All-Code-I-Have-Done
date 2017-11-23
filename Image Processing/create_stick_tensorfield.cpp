#include "tvf.h"

#include <cstdio>
double DF(double x, double y) {
	double theta = atan2(y, x);
	theta = abs(theta);
	if (theta > PI / 2.0) theta = PI - theta;
	//theta *= 4; //???
	if (theta > KERNEL_ARC) return 0;
	double l = sqrt(x * x + y * y);
	double c = (-16 * log2(0.1) * (sigma - 1)) / (PI * PI);
	double s = l;
	double k = 0;
	if (fabs(l) > DBL_EPSILON){
		if (fabs(theta) > DBL_EPSILON) s = theta * l / sin(theta);
		k = 2 * sin(theta) / l;
	}
	double ret = exp(-((s * s + c * k * k) / (sigma * sigma)));

	return ret;
}


inline void rotVector(double *rot, int x, int y, double &nx, double &ny) {
	nx = x * rot[0] + y * rot[1];
	ny = x * rot[2] + y * rot[3];
	x = nx;
	y = ny;
	return;
}


void create_stick_tensorfield(std::vector<std::vector<node>> &stf, double x, double y, bool dir) {
	double btheta = atan2(y, x);
	create_stick_tensorfield(stf, btheta, dir);
	return;
}
//sigma defined in global domain
void create_stick_tensorfield(std::vector<std::vector<node>> &stf, double btheta, bool dir) {
	
	
	double rotT[4];//rot matrix transpose
	double theta;

//	std::cout << "printing df matrix" << std::endl;
	int indX, indY; // need to rotate
	double rotX, rotY;
	rotT[0] = cos(btheta);
	rotT[1] = sin(btheta);
	rotT[2] = -sin(btheta);
	rotT[3] = cos(btheta);

	for (int i = 0; i < WS; ++i) {
		indY = -i + WHALF;
		for (int j = 0; j < WS; ++j) {
			indX = j - WHALF;
						
			//rotate [x, y]'
			rotVector(rotT, indX, indY, rotX, rotY);
			theta = atan2(rotY, rotX);


			//rotate filter
			double gamma = 2 * theta + btheta;

			//calc attenuation
			double df = DF(rotX, rotY);


			double cs = cos(gamma);
			double si = sin(gamma);
			
			//stf[(i * WS + j) * 4 + 0] = df * si * si;
			//stf[(i * WS + j) * 4 + 1] = df * (-si) * cs;
			//stf[(i * WS + j) * 4 + 2] = df * (-si) * cs;
			//stf[(i * WS + j) * 4 + 3] = df * cs * cs;
			if (!dir) {
				stf[i][j].tensor[0] = df * si * si;
				stf[i][j].tensor[1] = df * (-si) * cs;
				stf[i][j].tensor[2] = df * (-si) * cs;
				stf[i][j].tensor[3] = df * cs * cs;
			}
			else {
				stf[i][j].tensor[0] = df * cs * cs;
				stf[i][j].tensor[1] = df * si * cs;
				stf[i][j].tensor[2] = df * si * cs;
				stf[i][j].tensor[3] = df * si * si;
			}

			//std::cout << df << ' ';
		//	printf("%.7f ", df);
		}
		
	//	std::cout << std::endl;
	}
	return;
}