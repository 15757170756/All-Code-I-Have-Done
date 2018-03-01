#include "tvf.h"
//CrackPreDetection(grayImg, cracks, peakFlags, deri, theta);
int CrackPreDetection(
	cv::Mat &src,
	FImage &cracks,
	FImage &peakFlag,
	FImage &deriMag,
	FImage &deriTh,
	FImage &contrastImg,
	float& sigma,
	int& seedsRange,
	double thres,	
	int nonMaximaSupressRadius,
	int cutLenthLowerBound
	
	) {
	

	int w = src.cols;
	int h = src.rows;
	FImage voteMag, voteTh, votePeak;
	FImage outSeeds;
	FImage outTh;
	FImage gray;
	
#ifdef NEWDESIGN

	gray.allocate(w, h);
	//ImageIO::CvmatToPixels(src, gray.pData, src.cols, src.rows, 1);
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j)
			gray[i * w + j] = src.data[i * w + j];
	}
	if (peakFlag.IsEmpty()) {
		peakFlag.allocate(w, h);
	}
	if (deriMag.IsEmpty()) {
		deriMag.allocate(w, h);
	}
	if (deriTh.IsEmpty()) {
		deriTh.allocate(w, h);
	}
	newDesign::calcGradient(gray, deriMag, deriTh,sigma);
	newDesign::seedsFlow(deriMag, deriTh, outSeeds, outTh, peakFlag,contrastImg,seedsRange);
#else
	CT::seedsFlow(src, outSeeds, outTh);
#endif
	TensorVoting_new(voteMag, voteTh, outSeeds, outTh);
	

	//, thres, nonMaximaSupressRadius;
	voteMag.normalize(0.0, 1.0);
	//for (int i = 0; i < h; ++i)
	//	for (int j = 0; j < w; ++j) {
	//		
	//	}
	//voteMag.imshow("normalized votemag");
	voteMag.threshold(thres, 1.0);	
	votePeak.allocate(w, h);
	GetLocalPeak_orth(voteMag, voteTh, votePeak, nonMaximaSupressRadius);
	votePeak.imshow("votePeak");
	votePeak.imwrite("D:\\BridgeProject\\ImgWrite\\temp\\6.votePeak.jpg");
	//votePeak.imwrite("votePeak.png");
	//voteTh.imagesc("votePeak th");


	//testTres(dst);
	FImage cutted;
	myDesign::cutItViaLength(cutted, votePeak, cutLenthLowerBound);

#ifdef CUT_AROUND
	FImage cutted_new;
	myDesign::cutItAround(cutted_new, votePeak, 7);
#endif
	if (cracks.IsEmpty()) {
		cracks.allocate(w, h);
	}
	for (int i = 0; i < w * h; ++i)
		cracks[i] = cutted[i] > 0 ? 255 : 0;
	return w * h;
}

