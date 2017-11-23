#include "tvf.h"
namespace newDesign {
	// normal direction
	void GetTheta(FImage& dx, FImage& dy, FImage& outTheta)
	{
		int w = dx.width();
		int h = dx.height();
		if (outTheta.IsEmpty()) {
			outTheta.allocate(w, h);
		}
		for (int i = 0; i < w*h; i++){
			outTheta[i] = atan2(dy[i], dx[i]); // -PI to PI
		}
	}


	void GetLocalPeak(FImage& deri, FImage& outPeakFlag) {
		int dx[4] = { 1, 1, 0, -1 };
		int dy[4] = { 0, -1, -1, -1 };

		int w = deri.width();
		int h = deri.height();
		int k;
		outPeakFlag.allocate(w, h);
		outPeakFlag.setValue(0);

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				for (k = 0; k < 4; ++k) {
					int ix = i + dx[k], iy = j + dy[k];
					if (ix >= 0 && iy >= 0 && ix < h && iy < w) {
						if (deri[i * w + j] < deri[ix * w + iy]) break;
					}
				}
				if (k != 4) continue;//outPeakFlag[i * w + j] = 1;
				int pos = -64, val = INT_MIN;
				for (int l = -7; l < 7; ++l) {
					int iix = i + dx[k] * l, iiy = j + dy[k] * l;
					if (iix >= 0 && iiy >= 0 && iix < h && iiy < w) {
						if (deri[iix * w + iiy] > val) {
							val = deri[iix * w + iiy];
							pos = l;
						}
					}
				}
				if (val != INT_MIN) {
					//cout << "yes" << endl;
					outPeakFlag[(i + dx[k] * pos) * w + j + dy[k] * pos] = 1;
				}


			}
		}
		return;
	}

	// the theta is normal vectors
	void GetLocalPeak(FImage& deri, FImage& theta, FImage& outPeakFlag)
	{
		// four normal directions ( pair of points for each: dx1, dy1, dx2, dy2 )
		int nbOffset[4][4] = { { 1, 0, -1, 0 }, { 1, 1, -1, -1 }, { 0, 1, 0, -1 }, { -1, 1, 1, -1 } };

		int w = deri.width();
		int h = deri.height();
		outPeakFlag.allocate(w, h);
		outPeakFlag.setValue(0);

		for (int i = 1; i < h - 1; i++){
			for (int j = 1; j < w - 1; j++){
				int idx = i*w + j;

				// get offset idx
				int offsetIdx = 0;
				float th = theta[idx];
				if (th < 0) th += PI;

				if (th > PI / 8 && th <= 3 * PI / 8)
					offsetIdx = 1;
				else if (th > 3 * PI / 8 && th <= 5 * PI / 8)
					offsetIdx = 2;
				else if (th > 5 * PI / 8 && th <= 7 * PI / 8)
					offsetIdx = 3;

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
				}
			}
		}
	}
	// outTh is tangent vectors
	void FindSeeds(FImage& peakFlag, FImage& deri, FImage& theta, FImage& outSeeds, FImage& outTh,FImage &contrastImg,int& seedsRange)
	{
		int w = peakFlag.width();
		int h = peakFlag.height();

		outSeeds.allocate(w, h);
		outTh.allocate(w, h);
		outSeeds.setValue(-1);
		outTh.setValue(-1);
		contrastImg.allocate(w, h);
		// normal directions
		int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
		int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
		int extN = seedsRange;

		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				int idx = i*w + j;
				if (!peakFlag[idx]) continue;

				float currTh = theta[idx];
				float currDe = deri[idx];

				// get offset idx
				int offsetIdx = (theta[idx] + PI - PI / 8) / (PI / 4);
				if (theta[idx] < -7 * PI / 8){
					offsetIdx = 7;
				}

#if 0
				for (float k = -PI; k <= PI; k += PI / 32){
					int offsetIdx = (k + PI - PI / 8) / (PI / 4);
					if (k < -7 * PI / 8)
						offsetIdx = 7;
					printf("%d, %d\n", (int)(180 * k / PI), offsetIdx);
				}
#endif

				int x = j, y = i;
				for (int k = 1; k <= extN; k++){
					x += nbNx[offsetIdx];
					y += nbNy[offsetIdx];
					if (x < 0 || x >= w || y < 0 || y >= h) break;

					int tidx = y*w + x;
					if (peakFlag[tidx]){
						float th = theta[tidx];
						float de = deri[tidx];
						float diff = abs(currTh - th);
						if (diff > 3 * PI / 4 && diff < 5 * PI / 4){
							float minR = __min(de, currDe);
							float maxR = __max(de, currDe);
							int cx = (float)(x + j) / 2 + 0.5;
							int cy = (float)(y + i) / 2 + 0.5;
							int cIdx = cy*w + cx;
							if (maxR / minR < 3)
							{
								outSeeds[cy*w + cx] = (de + currDe) / 2.;
								//outSeeds[cy*w + cx] = response;
								//outSeeds[idx] = 1;
								//outSeeds[tidx] = 1;

#if 0
								float tmpTh = currTh;
								if (tmpTh < 0) tmpTh += PI;
#else
								float tmpTh = PI - (currTh + th) / 2.; // change to tangent direction
								if (tmpTh < 0) tmpTh += PI;
								if (tmpTh > PI) tmpTh -= PI;
#endif
								float midR = deri[cIdx];
								outTh[cy*w + cx] = tmpTh; // 0 ~ PI
								contrastImg[cIdx] = 1.0 - (2 * midR) / (minR + maxR);
							}
						}
						break;
					}
				}
			}
		}

#if 0
		FImage tmpSeedsFlag(w, h);
		tmpSeedsFlag.setValue(0);
		for (int i = 0; i < w*h; i++){
			if (outSeeds[i] > 0){
				tmpSeedsFlag[i] = 1;
			}
		}
		tmpSeedsFlag.imshow("seeds pos");
#endif
	}

	void GetDxDy(FImage& img, FImage& dx, FImage& dy)
	{
		float xKernel[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
		float yKernel[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

		int w = img.width();
		int h = img.height();
		dx.allocate(w, h);
		dy.allocate(w, h);

		ImageProcessing::filtering(img.pData, dx.pData, w, h, 1, xKernel, 1);
		ImageProcessing::filtering(img.pData, dy.pData, w, h, 1, yKernel, 1);
	}

	void ShowCracks(FImage& crackIDs)
	{
		int w = crackIDs.width();
		int h = crackIDs.height();

		FImage showImg(w, h, 3);
		showImg.setValue(0);

		for (int i = 0; i < w*h; i++){
			if (crackIDs[i] >= 0){
				float randColor[3];
				srand(crackIDs[i]);
				randColor[0] = (rand() % 128 + 128) / 255.;
				randColor[1] = (rand() % 128 + 128) / 255.;
				randColor[2] = (rand() % 128 + 128) / 255.;
				float* pDst = showImg.pData + 3 * i;
				memcpy(pDst, randColor, 3 * sizeof(float));
			}
		}

		//showImg.imshow("Final Cracks", 0);
	}

	float EulidDistance(int x1, int y1, int x2, int y2)
	{
		return sqrt((float)(x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}

	void OutputSeeds(FImage& seeds, FImage& th, char* outFileName)
	{
		int w = seeds.width();
		int h = seeds.height();

		int cnt = 0;
		for (int i = 0; i < w*h; i++){
			if (seeds[i] > 0)
				cnt++;
		}

		FILE* fp = fopen(outFileName, "wt");
		fprintf(fp, "%d\n", cnt);
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				int idx = i*w + j;
				if (seeds[idx] > 0){
					fprintf(fp, "%d %d %.1f\n", i, j, th[idx] * 180 / PI);
				}
			}
		}
		fclose(fp);
	}

	void calcGradient(FImage &gray, FImage &deri, FImage &theta,float& sigma) {
		gray.smoothing(sigma);
		//gray.GaussianSmoothing(2, 2);

		//gray.imshow("img");

		int w = gray.width();
		int h = gray.height();

		FImage dx, dy;
		//gray.dx(dx, true);
		//gray.dy(dy, true);
		GetDxDy(gray, dx, dy);

		//FImage deri(w, h);
		float mx, mi;
		mx = 0.0f;
		mi = INT_MAX;
		for (int i = 0; i < w*h; i++){
			deri[i] = sqrt(dx[i] * dx[i] + dy[i] * dy[i]);
			mx = max(mx, deri[i]);
			mi = min(mi, deri[i]);
		}
		//cout << "deri max = " << mx << endl;
		//cout << "deri min = " << mi << endl;
		deri.imagesc("deri");
		deri.imwrite("D:\\BridgeProject\\ImgWrite\\temp\\2.deri.jpg");
		//FImage theta;
		GetTheta(dx, dy, theta);
		//theta.imagesc("th");
	}

	void seedsFlow(FImage &deri, FImage &theta, FImage &outSeeds, FImage &outTh, FImage &peakFlag,FImage &contrastImg,int& seedsRange) {
		int w, h;
		w = deri.width();
		h = deri.height();
		//FImage peakFlag;
		GetLocalPeak(deri, theta, peakFlag);
		peakFlag.imwrite("D:\\BridgeProject\\ImgWrite\\temp\\3.peakFlag.jpg");
		peakFlag.imshow("PeakFlag");
		FImage peakTheta(theta);
		for (int i = 0; i < w*h; i++){
			if (!peakFlag[i])
				peakTheta[i] = -PI;
		}
		//peakTheta.imagesc("th Peak");

		//FImage outLabels;
		//ConnectPeaks(peakFlag, outLabels);
		//outLabels.imagesc("lab");

		FImage gapMap;
		//GapFilter1(deri, theta, gapMap);
		// 	for (int i = 0; i < w*h; i++){
		// 		if (gapMap[i] < 0)
		// 			gapMap[i] = 0;
		// 	}
		//	gapMap.imagesc("gap");

		//FImage outSeeds, outTh;
		FindSeeds(peakFlag, deri, theta, outSeeds, outTh,contrastImg,seedsRange);
		//getSeeds(gray, w, h, outSeeds);


		//OutputSeeds(outSeeds, outTh, "xx.edge");
	}



}