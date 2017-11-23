#include "tvf.h"
void calc_vote_ball(std::vector<std::vector<node> > &ball, FImage& seeds, std::vector<std::vector<node> > &T, std::vector<std::vector<std::vector<node>> > &cachedvf, bool dir) {
	std::vector<std::vector<node> > pbf(WS, std::vector<node>(WS));
	create_ball_tensorfield(pbf,cachedvf, dir);
	double ev[6];
	//FImage ball_mag(WS, WS);
	//ball_mag.allocate(WS, WS);
	
	
	/**/
	//std::cout << "printing ball tensorfiled" << std::endl;
	//for (int i = 0; i < WS; ++i) {
	//	for (int j = 0; j < WS; ++j) {
	//		convert_tensor_ev(pbf[i][j].tensor, ev);
	//		printf("%.7f ", ev[0]);
	//	}
	//	printf("\n");
	//}
	//for (int i = 0; i < WS; ++i) {
	//	for (int j = 0; j < WS; ++j) {
	//		convert_tensor_ev(pbf[i][j].tensor, ev);
	//		/*		std::cout << pbf[i][j].tensor[0] << ' ';
	//				std::cout << pbf[i][j].tensor[1] << ' ';
	//				std::cout << pbf[i][j].tensor[2] << ' ';
	//				std::cout << pbf[i][j].tensor[3] << ' ';*/
	//		ball_mag[i* WS + j] = ev[1];
	//	}
	//	//std::cout << std::endl;
	//}
	//ball_mag.imagesc("ball_mag");
	int anchorX = WHALF, anchorY = WHALF;
	
	int hei = T.size() - WHALF * 2;
	int wid = T[0].size() - WHALF * 2;
	for (int i = anchorY; i < anchorY + hei; ++i) {
		for (int j = anchorX; j < anchorX + wid; ++j) {
			double factor = seeds[(i - anchorY) * wid + j - anchorX];
			convert_tensor_ev(T[i][j].tensor, ev);
			// factor = 0 => ball tensor
			if (fabs(ev[0]) < DBL_EPSILON || ev[0] < 0) continue;
			//TODO: cachedvf
			/*std::cout << factor << std::endl;*/
			for (int k = -WHALF; k <= WHALF; ++k) {
				for (int l = -WHALF; l <= WHALF; ++l) {
					int nx = i + k, ny = j + l;
					ball[nx][ny].tensor[0] += pbf[k + WHALF][l + WHALF].tensor[0] * factor;
					ball[nx][ny].tensor[1] += pbf[k + WHALF][l + WHALF].tensor[1] * factor;
					ball[nx][ny].tensor[2] += pbf[k + WHALF][l + WHALF].tensor[2] * factor;
					ball[nx][ny].tensor[3] += pbf[k + WHALF][l + WHALF].tensor[3] * factor;
				}
			}
		}

	}
	return;

}
