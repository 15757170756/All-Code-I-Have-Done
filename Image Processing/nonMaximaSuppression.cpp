#include "tvf.h"
void GetLocalPeak_orth(FImage& deri, FImage& theta, FImage& outPeakFlag, const int r)
{
	// four normal directions ( pair of points for each: dx1, dy1, dx2, dy2 )
	//int nbOffset[4][4] = { { 1, 0, -1, 0 }, { 1, 1, -1, -1 }, { 0, 1, 0, -1 }, { -1, 1, 1, -1 } };
	int nbOffset[4][4] = { { 1, 0, -1, 0 }, { 1, -1, -1, 1 }, { 0, 1, 0, -1 }, { 1, 1, -1, -1 } };
	int w = deri.width();
	int h = deri.height();
	outPeakFlag.allocate(w, h);
	outPeakFlag.setValue(0);

	for (int i = 1; i < h - 1; i++){
		for (int j = 1; j < w - 1; j++){
			int idx = i*w + j;

			// get offset idx
			int offsetIdx = 2;
			float th = theta[idx];
			//if (th < 0) th += PI;
			th = fabs(th);

			if (th > PI / 8 && th <= 3 * PI / 8)
				offsetIdx = 3;
			else if (th > 3 * PI / 8 && th <= 5 * PI / 8)
				offsetIdx = 0;
			else if (th > 5 * PI / 8 && th <= 7 * PI / 8)
				offsetIdx = 1;

			// get neighbor idx
			int nb1x = j + nbOffset[offsetIdx][0];
			int nb1y = i + nbOffset[offsetIdx][1];
			int nb2x = j + nbOffset[offsetIdx][2];
			int nb2y = i + nbOffset[offsetIdx][3];

			float nb1v = deri[nb1y*w + nb1x];
			float nb2v = deri[nb2y*w + nb2x];
			float curr = deri[idx];
			if (curr >= nb1v && curr > nb2v
				|| curr > nb1v && curr >= nb2v){
				outPeakFlag[idx] = 1;
				//	cout << "************" << endl;
				//	cout << i << ' ' << j << ' ' << curr << ' '<<theta[idx] * 180 / PI<<endl;;
				for (int l = -r; l < r; ++l) {
					int nx, ny, nidx;
					nx = j + nbOffset[offsetIdx][0] * l;
					ny = i + nbOffset[offsetIdx][1] * l;
					nidx = ny * w + nx;
					if (ny >= 0 && ny < h && nx >= 0 && nx < w && deri[nidx] < curr) {
						//	cout << ny << ' ' << nx <<' '<<deri[nidx]<<' '<<theta[nidx] * 180 / PI<< endl;
						outPeakFlag[nidx] = 0;
					}

				}
			}

		}
	}
}
