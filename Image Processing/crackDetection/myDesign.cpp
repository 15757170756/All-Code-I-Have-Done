#include "tvf.h"
namespace myDesign{
	int entropyThres(cv::Mat &enhanced_gray, int baseY, int baseX, int w, int h) {
		int cnt[256];
		for (int i = 0; i < 256; ++i)
			cnt[i] = 0;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j)	{
				++cnt[enhanced_gray.at<uchar>(baseX + i, baseY + j)];
			}
		}
		double P[256], H[256], p;
		double Nd = w * h, acc, accp;
		int halfPixels = Nd / 2, accCnt, thres1;
		accCnt = 0;
		for (int i = 0; i < 256; ++i) {
			accCnt += cnt[i];
			if (accCnt >= halfPixels) {
				thres1 = i;
				break;
			}
		}
		acc = 0;
		accp = 0;
		//cout << "enhanced gray " <<Nd<< endl;
		for (int i = 0; i < 256; ++i){
			p = cnt[i] / Nd;
			if (cnt[i] != 0) {
				acc += p * log(p);
			}
			accp += p;
			H[i] = -acc;
			P[i] = accp;
			//printf("%lf ", P[i]);
		}
		double maxEntropy = DBL_MIN, HA, HB;
		int cand = -1;
		for (int s = 0; s < 256; ++s) {
			if (fabs(P[s]) < DBL_EPSILON || (1.0 - P[s]) < DBL_EPSILON) continue;
			//	cout << s << ' ';
			HA = log(P[s]) + H[s] / P[s];
			HB = log(1.0 - P[s]) + (H[255] - H[s]) / (1.0 - P[s]);
			//cout << '['<<s<<' '<<HA <<' '<< HB << "] ";
			if (HA + HB > maxEntropy) {
				maxEntropy = HA + HB;
				cand = s;
			}
		}
		//return cand;
		return max(thres1, cand);
	}
	void gradientCalc(cv::Mat &in, cv::Mat &gradMag, cv::Mat &gradTh) {
		int w, h;
		w = in.cols;
		h = in.rows;

		int ddepth = CV_32F;
		if (gradMag.empty()) {
			gradMag.create(h, w, ddepth);
		}
		if (gradTh.empty()) {
			gradTh.create(h, w, ddepth);
		}
		cv::Mat grad_x, grad_y;
		int scale = 1;
		int delta = 0;
		cv::GaussianBlur(in, in, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT); //reduce noise
		cv::Sobel(in, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
		cv::Sobel(in, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);


	
		cv::magnitude(grad_x, grad_y, gradMag);
		cv::normalize(gradMag, gradMag, 1, 0, cv:: NORM_MINMAX);

		cv::phase(grad_x, grad_y, gradTh);
	//	cv::imshow("gradMag", gradMag);
		


		

	}

	//void entropyThres() {
	//	//////////////////////////////////////////////////////////////////////////
	//	// entropy thres
	//	//int thres = getThreshold(dst, w, h);
	//	//cout << "entropy threshold  = " << thres << endl;
	//	//cv::Mat maskPic;
	//	//cv::threshold(dst, maskPic, thres + 1, 255, CV_THRESH_BINARY);
	//	//cv::imshow("thres", maskPic);
	//	////getSeeds(dst, w, h, thresSeeds, maskPic);
	//	//thresSeeds.imshow("init_seeds");
	//	//thresSeeds.imwrite("init_seeds.png");
	//	//////////////////////////////////////////////////////////////////////////
	//}


}



