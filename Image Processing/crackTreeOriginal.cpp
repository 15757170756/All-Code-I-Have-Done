#include "tvf.h"
namespace CT{
	void shadowRemoval(cv::Mat &src, cv::Mat &enhanced) {
		int w, h;

		cv::Mat smooth;
		src.copyTo(smooth);
		h = src.rows;
		w = src.cols;
		if (enhanced.empty()) {
			enhanced.create(h, w, CV_8UC1);
		}


		int morph_size = 2;
		cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));
		morphologyEx(smooth, smooth, cv::MORPH_CLOSE, element);
		int gaussian_ws = 2 * 30 + 1;
		cv::GaussianBlur(smooth, smooth, cv::Size(gaussian_ws, gaussian_ws), 0, 0);

		int histSize = 256; //from 0 to 255
		float range[] = { 0, 256 }; //the upper boundary is exclusive
		const float* histRange = { range };
		bool uniform = true;
		bool accumulate = false;
		cv::Mat hist;
		cv::calcHist(&smooth, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
		//cout << hist.rows << ' ' << hist.cols << endl;

		//cout << hist << endl;
		//cout << hist.type() << endl;
		//for (int i = 0; i < 256; ++i)
		//	cout << hist.at<float>(i) << ' ';
		//cout << endl;

		int pixelNum = src.rows * src.cols;
		float p[256];
		float val;
		int acc;

		int LEVEL = 240, LOW;
		int ng = pixelNum / LEVEL;
		vector<int> level;
		acc = 0;
		int bound = 0;
		//	freopen("out.txt", "w", stdout);
		for (int i = 0; i < 256; ++i) {
			acc += static_cast<int>(hist.at<float>(i));
			if (acc >= ng) {
				//cout << i << ' ' << acc << endl;
				level.push_back(i);
				acc = 0;
			}
		}
		if (acc != 0) level.push_back(255);
		//cout << level.size() << endl;
		LEVEL = level.size();
		LOW = LEVEL / 8 * 7;

		//print(level);
		bound = level[LOW - 1];
		//cout << bound << endl;



		LEVEL = LOW + 1;
		level[LOW] = 255;

		vector<int> levelIdx(256, 0);

		int l, r;
		l = r = 0;
		for (int i = 0; i < LEVEL; ++i) {
			r = level[i];
			for (int j = l; j <= r; ++j) {
				levelIdx[j] = i;
				//cout << j << ' ' << levelIdx[j] << endl;
			}
			l = r + 1;
		}
		//print(levelIdx);
		vector<vector<int> > preTheta(LEVEL, vector<int>(256, 0));
		int diff;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				val = smooth.at<uchar>(i, j);
				diff = src.at<uchar>(i, j);
				preTheta[levelIdx[val]][diff]++;
			}
		}
		vector<float> sd(LEVEL), e(LEVEL);

		for (int i = 0; i < LEVEL; ++i) {
			int pixels = 0;
			for (int j = 0; j < 256; ++j) {
				pixels += preTheta[i][j];
			}
			//cout <<"bin "<< i << ' ' << ' '<<level[i]<< ' '<<pixels << ' ';
			double ex, ex2;
			ex = ex2 = 0;
			for (int j = 0; j < 256; ++j) {
				ex2 += static_cast<double>(preTheta[i][j]) * j * j;
				ex += static_cast<double>(preTheta[i][j]) * j;
			}
			ex2 /= pixels;
			ex /= pixels;
			e[i] = ex;
			//cout << e[i] << ' ';
			sd[i] = sqrt(ex2 - ex * ex);
			//cout << e[i]<<' '<<sd[i] << endl;
		}
		//cout << endl;
		vector<float> D(256), I(256);
		for (int i = 0; i < 256; ++i) {
			D[i] = sd[levelIdx[i]];
			I[i] = e[levelIdx[i]];
		}
		//FImage enhanced_gray(w, h);

		float Ib, Db;
		//
		Ib = e[LEVEL - 1];
		Db = sd[LEVEL - 1];
		//cout << Ib << ' ' << Db << endl;
		float cur;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				val = smooth.at<uchar>(i, j);
				cur = static_cast<float>(src.at<uchar>(i, j));
				if (val < bound) {
					if (cur == I[val])
					{
						cur = Ib;
					}
					else {
						cur = Db * (cur - I[val]) / D[val] + Ib;
					}
				}
				cur = max(0.0f, cur);
				cur = min(cur, 255.0f);
				enhanced.at<uchar>(i, j) = cur;
			}
		}
		return;

	}
	int getSeeds(cv::Mat &enhanced, FImage &outSeeds) {
		int thres[256];
		int w = enhanced.cols;
		int h = enhanced.rows;
		if (outSeeds.IsEmpty()) {
			outSeeds.allocate(w, h);
		}
		cv::imshow("enhanced image", enhanced);
		//	cout << mask.type << endl;
		memset(thres, 0, sizeof(thres));
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				double val = 0;
				int cnt = 0;
				//if (mask.at<uchar>(i, j)) continue;
				for (int k = -1; k < 2; ++k) {
					for (int l = -1; l < 2; ++l) {
						int nx = i + k, ny = j + l;
						if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
							val += enhanced.at<uchar>(nx, ny);
							++cnt;
						}
					}
				}
				val -= cnt * enhanced.at<uchar>(i, j);
				//cout << val << endl;
				//Thres[i * w + j] = val;
				thres[enhanced.at<uchar>(i, j)] += val;
			}
		}
		int T = 0;
		for (int i = 0; i < 256; ++i) {
			if (thres[i] > thres[T]) T = i;
		}
		//cout << "T = " << T << endl;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {

				if (enhanced.at<uchar>(i, j) < T) {
					outSeeds[i * w + j] = 1;
					//cout << "yes" << endl;
				}
				else {
					outSeeds[i * w + j] = 0;

				}
			}
		}
		//cout << "seeds threshold " << T << endl;
		return T;

	}
	void seedsFlow(cv::Mat src, FImage &outSeeds, FImage &outTh){
		int w, h;
		w = src.cols;
		h = src.rows;
		cv::Mat gradMag, gradTh;
		myDesign::gradientCalc(src, gradMag, gradTh);



		cv::Mat enhancedGray;
		CT::shadowRemoval(src, enhancedGray);
//		FImage outSeeds;
		if (outSeeds.IsEmpty()) {
			outSeeds.allocate(w, h);
		}
//		FImage outTh;
		if (outTh.IsEmpty()) {
			outTh.allocate(w, h);
		}
		int T = CT::getSeeds(enhancedGray, outSeeds);

		cv::Mat maskPic;
		seedFilter(src, maskPic);


		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j)
				//if (maskPic.at<uchar>(i, j)  > 0) outSeeds[i * w + j] = 0;
			//	else {
					if (outSeeds[i * w + j] > 0) {
						outSeeds[i * w + j] = gradMag.at<float>(i, j);
						outTh[i * w + j] = PI / 2 - gradTh.at<float>(i, j);
					}
			//	}
		}



		//cv::Mat weight;
		//int gaussian_ws = 2 * 1 + 1;
		//cv::GaussianBlur(enhancedGray, weight, cv::Size(gaussian_ws, gaussian_ws), 0, 0);
	}
}