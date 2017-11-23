#include "tvf.h"
void calc_vote_stick(std::vector<std::vector<node> > &stick, std::vector<std::vector<node> > &T, std::vector<std::vector<std::vector<node>>> &cachedvf, FImage &init, bool dir) {
	int anchorX = WHALF, anchorY = WHALF;
	double eigVec[6];
	int hei = T.size() - WHALF * 2;
	int wid = T[0].size() - WHALF * 2;
	std::vector<std::vector<node> > ptf(WS, std::vector<node>(WS));
	for (int i = anchorY; i < anchorY + hei; ++i) {
		for (int j = anchorX; j < anchorX + wid; ++j) {
			if (init[(i - anchorY) * wid + j - anchorX] <= 0) continue;
			convert_tensor_ev(T[i][j].tensor, eigVec);
			double factor = eigVec[0] - eigVec[1];
			// factor = 0 => ball tensor
			if (fabs(factor) < DBL_EPSILON) continue;
			//TODO: cachedvf
			std::vector<std::vector<node> > *pptf;
#ifndef CACHE_STICK_FIELD
#if 0
			int angle = round(atan2(eigVec[2], -eigVec[3]));
			//double theta = angle / 180.0 * PI;
			create_stick_tensorfield(ptf, angle);
#endif
			//create_stick_tensorfield(ptf, -eigVec[3], eigVec[2]);
			create_stick_tensorfield(ptf, eigVec[2], eigVec[3], 1);
			pptf = &ptf;
			


#else
			//int angle = round(180.0 / PI * atan(eigVec[3] / eigVec[2]));
			//if (angle < 1) angle += 180;
			double theta;
			int angle;
			if (!dir) {
				//normal
				theta = atan2(eigVec[2], -eigVec[3]);// 
				if (theta < 0) theta += PI;
				angle = round(theta * 180.0 / PI);

			} else {
				//tangent
				theta = atan2(eigVec[3], eigVec[2]);
				if (theta < 0) theta += PI;
				angle = round(theta * 180.0 / PI) + 180;
			}
		//	int angle = round(atan2(eigVec[3], eigVec[2]) * 180.0 / PI) + 180;
			pptf = &(cachedvf[angle]);
#endif

			for (int k = -WHALF; k <= WHALF; ++k) {
				for (int l = -WHALF; l <= WHALF; ++l) {
					int nx = i + k, ny = j + l;
					stick[nx][ny].tensor[0] += (*pptf)[k + WHALF][l + WHALF].tensor[0] * factor;
					stick[nx][ny].tensor[1] += (*pptf)[k + WHALF][l + WHALF].tensor[1] * factor;
					stick[nx][ny].tensor[2] += (*pptf)[k + WHALF][l + WHALF].tensor[2] * factor;
					stick[nx][ny].tensor[3] += (*pptf)[k + WHALF][l + WHALF].tensor[3] * factor;
				}
			}
		}

	}
	return; 
}