#pragma once
#pragma warning(disable: 4996)
#include <cmath>
#include <vector>
#include "Image.h"
#include "ImageIo.h"
#include <time.h>
#include <cstdio>


//////////////////////////////////////////////////////////////////////////
//predefine argument

#define CPD_THRES 0.1
#define CPD_NON_MAXIMA_SUPRESS_DARIUS 1
#define CPD_CUT_LENGTH_LOWERBOUND 55 
#define NEWDESIGN 1


#define KERNEL_ARC (PI / 4.0)

//////////////////////////////////////////////////////////////////////////


int CrackPreDetection(
	cv::Mat &src,
	FImage &cracks,
	FImage &peakFlag,
	FImage &deriMag,
	FImage &deriTh,
	FImage& contrastImg,
	float& sigma,
	int& seedsRange,	
	double thres = CPD_THRES,
	int nonMaximaSupressRadius = CPD_NON_MAXIMA_SUPRESS_DARIUS,
	int cutLenthLowerBound = CPD_CUT_LENGTH_LOWERBOUND	
	);

//
#if (_MSC_VER < 1800)
inline double round(double value) { return value < 0 ? -std::floor(0.5 - value) : std::floor(0.5 + value); }
inline double log2(double value) { return log(value) / log(2.0); };
#endif

class node {
public:
	double tensor[4];
	double ev[6];
	friend node operator+(const node &lhs, const node &rhs);
	node(){ 
		tensor[0] = 0.0;
		tensor[1] = 0.0;
		tensor[2] = 0.0;
		tensor[3] = 0.0;
	}
	node(const node &other) {
		tensor[0] = other.tensor[0];
		tensor[1] = other.tensor[1];
		tensor[2] = other.tensor[2];
		tensor[3] = other.tensor[3];
	}
	node& operator=(const node &other);
	node& operator+=(const node& rhs);

};



//
//const double PI = std::atan(1.0) * 4;
const double sigma = 9;
const int WS = floor(ceil(sqrt(-log(0.01) * sigma *sigma) * 2) / 2) * 2 + 1;
const int WHALF = (WS - 1) / 2;
//
void convert_tensor_ev(double *tensor, double *ev);
double DF(double x, double y, double sigma);
inline void rotVector(double *rot, double &x, double &y);
void create_stick_tensorfield(std::vector<std::vector<node>> &stf, double x, double y, bool dir);
void create_stick_tensorfield(std::vector<std::vector<node>> &stf, double btheta, bool dir);
void create_ball_tensorfield(std::vector<std::vector<node> > &blf, std::vector<std::vector<std::vector<node>> > &cachedvf, bool dir);

void calc_sparse_field(std::vector<std::vector<node> > &T,FImage& seeds);
void calc_vote_ball(std::vector<std::vector<node> > &ball, FImage& seeds, std::vector<std::vector<node> > &T, std::vector<std::vector<std::vector<node>>> &cache, bool dir);
void convert_ev_tensor(double *ev, double *tensor);
void calc_vote_stick(std::vector<std::vector<node> > &stick, std::vector<std::vector<node> > &T, std::vector<std::vector<std::vector<node>>> &cache, FImage &init, bool dir);
void TensorVoting_new(FImage& voteMag, FImage& voteTh, FImage& seeds, FImage &seedTh);
void create_cached_vf(std::vector<std::vector<std::vector<node>>> &cache);

void cutIt(FImage &cutted, FImage &ori, int thres);
void GetLocalPeak_orth(FImage& deri, FImage& theta, FImage& outPeakFlag, const int r);

void testTres(cv::Mat &srcI);

void seedFilter(cv::Mat in, cv::Mat &maskPic);
void cutItAround(FImage &cutted, FImage &ori, int r);
#define SUPRESS_BALL 1
#define CACHE_STICK_FIELD 1
//#define TEST 1
//#define DEBUG 1




namespace CT{
	//crack tree original method
	void shadowRemoval(cv::Mat &src, cv::Mat &enhanced);
	int getSeeds(cv::Mat &enhanced, FImage &outSeeds);
	void seedsFlow(cv::Mat src, FImage &outSeeds, FImage &outTh);
}

namespace myDesign{
	void cutItViaLength(FImage &cutted, FImage &ori, int thres);
	void cutItAround(FImage &cutted, FImage &ori, int r);
	int entropyThres(cv::Mat &enhanced_gray, int baseY, int baseX, int w, int h);
	void gradientCalc(cv::Mat &in, cv::Mat &gradMag, cv::Mat &gradTh);
}

namespace newDesign{
	//new seeds method
	void seedsFlow(FImage &deri, FImage &theta, FImage &outSeeds, FImage &outTh, FImage &peakFlag,FImage &contrastImg,int& seedsRange);
	void calcGradient(FImage &gray, FImage &deriMag, FImage &deriTh,float& sigma);

}