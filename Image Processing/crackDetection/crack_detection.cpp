#include "crack_detection.h"
#include <stdio.h>
#include <vector>

#include "opencv2/imgproc.hpp"
#include "highgui.hpp"
#include "Image.h"
#include"Graph.h"
#include<opencv2/opencv.hpp>
#include "dt.h"
#include "Heap.h"
#include<algorithm>
#include<stdlib.h>
#include"tvf.h"
#include<ctime>
#include <cmath>
#include"ImageIO.h"
#define DERI_TH  (30/255.)
#define WIDTH  1296
#define HEIGHT  864
#define P    8


int getLowestPix(cv::Mat& grayImg, int row, int col){
	int w = grayImg.cols;
	int h = grayImg.rows;
	int min = grayImg.at<uchar>(row, col);
	int pixX = col;
	int pixY = row;
	for (int i = row; i < row + P; i++){
		for (int j = col; j < col + P; j++){
			if (i < 0 || i >= h || j < 0 || j >= w){
				continue;
			}
			if (min >= grayImg.at<uchar>(i, j)){
				pixX = j;
				pixY = i;
				min = grayImg.at<uchar>(i, j);
			}

		}
	}
	return pixY*w + pixX;
}
void getSeedsImg(cv::Mat& grayImg, FImage& seedsFilter){
	int w = grayImg.cols;
	int h = grayImg.rows;
	std::cout << "图像的宽度为：" << w << endl;
	std::cout << "图像的高度为：" << h << endl;
	FImage seeds;
	seeds.allocate(w, h);
	seeds.setValue(0);
	int seedCnt = 0;
	for (int i = 0; i < h; i = i + P){
		for (int j = 0; j < w; j = j + P){
			int loc = getLowestPix(grayImg,i, j);
			seedCnt++;
			seeds[loc] = seedCnt;
			
		}
	}
	cv::Mat mean, stddev;
	cv::meanStdDev(grayImg, mean, stddev);
	/*std::cout << "mean的值为：" << mean <<endl;
	std::cout << "stddev的值为：" << stddev << endl;*/
	double pixMean = mean.at<double>(0, 0);
	double pixStdDev = stddev.at<double>(0, 0);
	std::cout << "mean的值为：" << pixMean;
	std::cout << "stddev的值为：" << pixStdDev;
	//计算阈值Te=mean-Ke*stddev,此处Ke取值1
	double Ke = 1;
	double Te = pixMean - Ke*pixStdDev;

	//下面注释的部分表示将每个P*P中最小的像素点显示在原始的grayImg上
	/*for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int id = i*w + j;
			if (seeds[id] > 0){
				grayImg.at<uchar>(i, j) = 255;
			}
		}
	}
	cv::imshow("seedGray", grayImg);
	cv::imwrite("D:\\BridgeProject\\ImgWrite\\tempResults\\9.graySeed.jpg", grayImg);*/


	//经过下面循环的步骤，seedsFilter中的>=0的像素点为每个grayImg中的每个P*P方块中的的最小像素点
	//其中等于0的像素点代表被阈值Te淘汰的种子点，大于0的为保留的种子点
	//seeds中的种子点的编号为1....n，其中w,h能整除n时，n=(w/8)*(h/8)，否则n=(w/8+1)*(h/8+1)
	seedsFilter.allocate(w, h);
	seedsFilter.setValue(-1);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int id = i*w + j;
			if (seeds[id] > 0){
				double pix = (double)grayImg.at<uchar>(i, j);
				if (pix <= Te){
					seedsFilter[id] = seeds[id];
				}
				else{
					seedsFilter[id] = 0;
				}
			}
			
		}
	}

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int id = i*w + j;
			if (seedsFilter[id] > 0){
				grayImg.at<uchar>(i, j) = 255;
			}
		}
	}
	cv::imshow("seedFilter", grayImg);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\tempResults\\2.seedFilter.jpg", grayImg);
}



double getmmperpixle(double distance, cv::Mat& src_image)
{
	cv::Mat src_gray;
	double mm_pix;
	int cannyThreshold = 23;
	int accumulatorThreshold = 25;
	int minRadius = 85;
	int maxRadius = 108;

	//将原图缩小5倍
	cv::resize(src_image, src_image,
		cv::Size(),
		0.2, 0.2,
		cv::INTER_AREA);

	cv::cvtColor(src_image, src_gray, CV_BGR2GRAY);
	cv::GaussianBlur(src_gray, src_gray, cv::Size(9, 9), 2, 2);

	std::vector<cv::Vec3f> circles;

	HoughCircles(src_gray, circles,
		cv::HOUGH_GRADIENT, 1,
		src_gray.cols ,
		cannyThreshold, accumulatorThreshold,
		minRadius, maxRadius);

	//获得圆的半径值（像素点）
	int pixRadius;
	pixRadius = (circles[0][2]);
	double realRadius = distance * tan(2.161652113 / 2 * CV_PI / 180);

	mm_pix = realRadius / (pixRadius * 5);
	return mm_pix;
}
static inline LONG64 Key(int i, int j)
{
	// swap: always i<j
	if (i > j) { int t = i; i = j; j = t; };
	return (LONG64)i + ((LONG64)j << 32);
}
static inline int KeyFirst(LONG64 i) { return int(i); }
static inline int KeySecond(LONG64 i) { return int(i >> 32); }

void GenerateTree(FImage& seeds, CMst& outTree)
{
	int w = seeds.width();
	int h = seeds.height();
	
	FImage cost(w, h);
	cost.setValue(1);

	FImage dis(w, h);
	IntImage labels(w, h);
	memset(dis.pData, 0x7F, w*h*sizeof(float)); // init approx. to FLT_MAX
	memset(labels.pData, 0xFF, w*h*sizeof(int)); // init to -1;

	FImage seedMask(w, h);
	seedMask.setValue(0);

	int* xID = new int[w*h];
	int* yID = new int[w*h];

	int cnt = 0;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int idx = i*w + j;
			if (seeds[idx] > 0.01){
				seedMask[idx] = 1;    
				labels[idx] = cnt;
				dis[idx] = cost[idx];
				xID[cnt] = j;
				yID[cnt] = i;
				cnt++;
			}
		}
	}
	GDT(cost.pData, dis.pData, labels.pData, w, h);
#if 0
	seedMask.imshow("seeds");
	cost.imshow("cost map");
	dis.imagesc("dis");
	labels.imagesc("labels", 0);
#endif

	int maxNb = 64;
	int numV = cnt;
	int numE = 0;
	int* edges = new int[2 * numV * maxNb];
	float* edgeLens = new float[numV * maxNb];
	float* edgeLensTmp = new float[numV*maxNb];//////////
	CHeap H(w*h, true);
	for (int i = 1; i < h; i++){
		for (int j = 1; j < w; j++){
			int idx = i*w + j;

			int l0 = labels[idx];
			int l1 = labels[idx - 1];
			int l2 = labels[idx - w];

			if (l0 != l1){
				LONG64 k = Key(l0, l1);
				double v = dis[idx] + dis[idx - 1];
				H.Push(&v, (double*)&k, 1);
			}

			if (l0 != l2){
				LONG64 k = Key(l0, l2);
				double v = dis[idx] + dis[idx - w];
				H.Push(&v, (double*)&k, 1);
			}
		}
	}
	while (H.Size()){
		LONG64 newK, currK;

		float minDis = H.Top((double*)&currK);
		int l0 = KeyFirst(currK);
		int l1 = KeySecond(currK);

		while (H.Size()){
			float dis = H.Top((double*)&newK);
			if (newK != currK){
				break;
			}
			H.Pop();

			if (dis < minDis){
				minDis = dis;
			}
		}
		
		
		edges[2 * numE + 0] = l0;
		edges[2 * numE + 1] = l1;
		edgeLens[numE] = minDis;
		numE++;
	}


	memcpy(edgeLensTmp,edgeLens,sizeof(float)*numE);//////
	sort(edgeLensTmp, edgeLensTmp+numE);/////////
	printf("the max length is: %f\n",edgeLensTmp[numE-1]);///////////

	outTree.Init(numV, numE, edges, edgeLens);

	//cv::Mat showImg(h, w, CV_8UC1);
	cv::Mat showImg(h, w, CV_32FC1);
	memset(showImg.data, 0, showImg.rows*showImg.step);
	for (int i = 0; i < numV; i++){
		int p = outTree.Parent(i);
		cv::line(showImg, cv::Point(xID[i], yID[i]), cv::Point(xID[p], yID[p]), CvScalar(254));
	}
	cv::imshow("MST", showImg);
	//cv::imwrite("MST.jpg",showImg);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\temp\\8.MST.jpg",showImg);
	//cv::waitKey(0);
	delete[] edgeLensTmp;
	delete[] edges;
	delete[] edgeLens;
	delete[] xID;
	delete[] yID;
}

bool isCut(int* root, int rootCnt, int id){
	for(int i = 0; i < rootCnt; i++){
		if(root[i] == id){
			return true;
		}
	}
	return false;

}
bool isInsideTree(int* curVer, int curVerCnt, int id){
	for(int i = 0; i < curVerCnt; i++){
		if(id == curVer[i])
			return true;
	}
	return false;
}


int getPathNum(int leaf, int* curVer,int curVerCnt, int* visited, int* verList, float* disList,float* tmpDisList, float& curLength,int* cuttedVer,int cuttedVerCnt,CMst& outTree){
	int listCnt = 0;
	verList[listCnt] = leaf;
	disList[listCnt] = 0;
	visited[verList[listCnt]] = 1;
	listCnt++;
	for(int c = 0; c < listCnt; c++){
		int parent = outTree.Parent(verList[c]);

		if(isInsideTree(curVer,curVerCnt,parent) && (visited[parent] == 0)
			&& (!isInsideTree(cuttedVer,cuttedVerCnt,parent))){
			verList[listCnt] = parent;
			visited[parent] = 1;
			float parentDis = outTree.ParentDistance(verList[c]);
			disList[listCnt] = disList[c] + parentDis;
			listCnt++;
		}

		int childNum = outTree.ChildNum(verList[c]);
		for(int m = 0; m < childNum; m++){
			int curChild = outTree.ChildIndex(verList[c])[m];
			if(isInsideTree(curVer,curVerCnt,curChild) && (visited[curChild] == 0)
				&& (!isInsideTree(cuttedVer,cuttedVerCnt,curChild))){
				verList[listCnt] = curChild;
				visited[curChild] = 1;
				float parentDis = outTree.ParentDistance(curChild);
				disList[listCnt] = disList[c] + parentDis;
				listCnt++;
			}
		}
	}

	memcpy(tmpDisList,disList,sizeof(float)*listCnt);
	sort(tmpDisList,tmpDisList+listCnt);//sort[firstAddress,lastAddress),左闭右开，不包括结尾地址的数

	curLength = tmpDisList[listCnt - 1];
	for(int i = 0; i < listCnt; i++){
		if(curLength == disList[i])
			return verList[i];
	}
	return -1;
	

}

int getPathVer(int start, int end, int* curVer, int curVerCnt,int* visited, int* verList,CMst& outTree){
	int top = -1;
	top++;
	verList[top] = start;
	visited[verList[top]] = 1;
	while(verList[top] != end){
		int parent = outTree.Parent(verList[top]);
		if(isInsideTree(curVer, curVerCnt, parent) && (visited[parent] == 0)){
			top++;
			verList[top] = parent;
			visited[parent] = 1;
		}else{
			int childNum = outTree.ChildNum(verList[top]);
			int m;
			for(m = 0; m < childNum; m++){
				int curChild = outTree.ChildIndex(verList[top])[m];
				if(isInsideTree(curVer,curVerCnt,curChild) && (visited[curChild] == 0)){
					top++;
					verList[top] = curChild;
					visited[curChild] = 1;
					break;
				}
			}

			if(m == childNum){
				top--;
			}

		}
	}
	//printf("start----------\n");
	//for(int i = 0; i <= top; i++){

	//	printf("%d   ",verList[i]);
	//}
	printf("the verlist[0] is:%d\n",verList[0]);
	printf("the verList[top] is:%d\n",verList[top]);
	return top + 1;
}


void CutToManyTree(FImage& gray , CMst& outTree){
	int w = gray.width();
	int h = gray.height();
	
	int cnt = 0;
	int numV = 0;
	int* xID = new int[w*h];
	int* yID = new int[w*h];
	std::cout <<"节点的个数是:"<< outTree.NodeCnt();//报错的原因是outTree中的个数为0
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			int id = i*w + j;
			if(gray[id] > 0.00){
				xID[cnt] = j;
				yID[cnt] = i;
				cnt++;
			}
		}
	}

	//printf("cnt:%d\n",cnt);
	numV = cnt;
	int* root = new int[numV];

	int rootCnt = 0;
	root[rootCnt] = 0;
	rootCnt++;
	for(int i = 1; i < numV; i++){
		if(outTree.ParentDistance(i) > 0.18){
			root[rootCnt] = i;
			rootCnt++;			
		}
	}

//	printf("cutToMany:rootCount: %d\n",rootCnt);
	//cv::Mat manyTree(h, w, CV_8UC3);
	cv::Mat manyTree(h, w, CV_32FC3);
	memset(manyTree.data, 0, manyTree.rows*manyTree.step);
	//cv::imshow("manyTree",manyTree);
	//cv::line(manyTree, cv::Point(1,5), cv::Point(6,10),CvScalar(123,97,86));
	//cv::imshow("manyTree",manyTree);
	for(int i = 0; i < rootCnt; i++){
		int* vertex = new int[numV];
		//srand(root[i]);
		float color1 = (rand() % 255);
		float color2 = (rand() % 255);
		float color3 = (rand() % 255);
		int verCnt = 0;
		vertex[verCnt] = root[i];
		verCnt++;
		//printf("curroot:%d\n",root[i]);
		for(int c = 0; c < verCnt; c++){
			int tmp = vertex[c];
			int m = outTree.ChildNum(tmp);
			for(int j = 0; j < m; j++){
				if(isCut(root, rootCnt, outTree.ChildIndex(tmp)[j])) 
					continue;
				vertex[verCnt] = outTree.ChildIndex(tmp)[j];		
				cv::line(manyTree, cv::Point(xID[tmp], yID[tmp]), cv::Point(xID[vertex[verCnt]],yID[vertex[verCnt]]),CvScalar(color1,color2,color3));
				verCnt++;
			}
		}
	//	printf("root:%d   VerCnt:%d     \n",root[i],verCnt);
		delete[] vertex;
	}

	cv::imshow("manyTree1", manyTree);
	//cv::imwrite("manyTree.png",manyTree);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\temp\\9.manytree.jpg",manyTree);
	//cv::waitKey(0);
	delete[] xID;
	delete[] yID;
	//return root;
}


float getWidth(int* xID, int* yID, int* verList, int pathVerCnt,FImage& theta,FImage& peakFlag){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int nbNyarr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int extN = 10;
	int cnt = 0;
	float width = 0;
	float maxWidth = 0;//临时添加
	float minWidth;

	for(int i = 0; i < pathVerCnt; i++){
		float tmpWidth = 1;//临时添加
		int flag = 0;
		int currX = xID[verList[i]];
		int currY = yID[verList[i]];
		int id = currY*w + currX;
		float th = theta[id];
		float dis = 0;
		
		int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
			if (theta[id] < -7 * PI / 8){
				offsetId = 7;
			}
			int x = currX;
			int y = currY;
		for(int k = 0; k < extN; k++){
			x += nbNx[offsetId];
			y += nbNy[offsetId];
			if(x < 0 || x >= w || y < 0 || y >= h) break;

			int nbId = y*w + x;
			if(peakFlag[nbId]){
				int xDis =abs(currX - x);
				int yDis =abs(currY - y);
				float euDis = sqrt(xDis * xDis + yDis * yDis);
				tmpWidth = tmpWidth + euDis;//临时添加
				dis += euDis;
				flag++;
				break;
			}
		}
			x = currX;
			y = currY;
		for(int k = 0; k < extN; k++){
			x += nbNxarr[offsetId];
			y += nbNyarr[offsetId];
			if(x < 0 || x >= w || y < 0 || y >= h){
				break;
			}
			int nbId = y*w + x;
			if(peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis* xDis + yDis*yDis);
				tmpWidth = tmpWidth + euDis;//临时添加
				dis += euDis;
				flag++;
				break;

			}
			
		}

		if(flag == 2){
			widthSum = widthSum + dis;
			cnt++;
		}
		if (tmpWidth > maxWidth){
			maxWidth = tmpWidth;		
		}
		if (i == 0){
			minWidth = tmpWidth;		
		}else{
			if (minWidth > tmpWidth){
				minWidth = tmpWidth;
			}
		}
	}
	//std::cout<<"the cnt is:"<<cnt<<endl;
	width = widthSum / cnt;
	std::cout << "最小值是-------" << minWidth << endl;//临时添加
	std::cout << "最大值是------------" << maxWidth << endl;//临时添加
	std::cout << "平均值是--------------------------" << width << endl;//临时添加
	std::cout << cnt << "  " << pathVerCnt << endl;
	return width;	
}
float getWidth1(int* xID, int* yID, int* verList, int pathVerCnt, FImage& theta, FImage& peakFlag){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int nbNyarr[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int extN = 10;
	int cnt = 0;
	float width = 0;
	float maxWidth = 0;//临时添加
	float minWidth;
	int maxCnt = 0;
	int* maxLocx = new int[w*h];
	int* maxLocy = new int[w*h];
	for (int i = 0; i < pathVerCnt; i++){
		float tmpWidth = 1;//临时添加
		int flag = 0;
		int currX = xID[verList[i]];
		int currY = yID[verList[i]];
		int id = currY*w + currX;
		float th = theta[id];
		float dis = 0;

		int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
		if (theta[id] < -7 * PI / 8){
			offsetId = 7;
		}
		int x = currX;
		int y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNx[offsetId];
			y += nbNy[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h) break;

			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis * xDis + yDis * yDis);
				tmpWidth = tmpWidth + euDis;//临时添加
				dis += euDis;
				flag++;
				break;
			}
		}
		x = currX;
		y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNxarr[offsetId];
			y += nbNyarr[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h){
				break;
			}
			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis* xDis + yDis*yDis);
				tmpWidth = tmpWidth + euDis;//临时添加
				dis += euDis;
				flag++;
				break;

			}

		}
		if (flag == 2){
			widthSum = widthSum + dis;
			cnt++;
		}
		else{
			widthSum = widthSum + tmpWidth;
		}
		if (tmpWidth > maxWidth){
			maxCnt = 0;
			maxWidth = tmpWidth;
			maxLocx[maxCnt] = currX;
			maxLocy[maxCnt] = currY;
			maxCnt = 1;
		}else if (tmpWidth == maxWidth){
			maxLocx[maxCnt] = currX;
			maxLocy[maxCnt] = currY;
			maxCnt++;
		}
		if (i == 0){
			minWidth = tmpWidth;
		}
		else{
			if (minWidth > tmpWidth){
				minWidth = tmpWidth;
			}
		}
	}
	//std::cout<<"the cnt is:"<<cnt<<endl;
	width = widthSum / pathVerCnt;
	std::cout << "最小值是-------" << minWidth << endl;//临时添加
	std::cout << "最大值是------------" << maxWidth << endl;//临时添加
	std::cout << "平均值是--------------------------" << width << endl;//临时添加
	std::cout << cnt << "  " << pathVerCnt << endl;
	std::cout << "宽度最大的坐标为：" << endl;
	for (int i = 0; i < maxCnt; i++){
		std::cout <<i<< ". [" << maxLocx[i] << "," << maxLocy[i] << "]" << endl;
	}
	
	return width;
}

float getWidth2(int* xID, int* yID, int* verList, int pathVerCnt, FImage& theta, FImage& peakFlag){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int nbNyarr[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int extN = 10;
	int cnt = 0;
	float maxWidth = 0;//临时添加
	int maxCnt = 0;
	float dis;
	float*  initWidth = new float[w*h];
	float*  rangeWidth = new float[w*h];
	int range = 6;//若range=20,即每个点的宽度为其左边10个、右边10个，及该点宽度之和再取平均值


	for (int i = 0; i < pathVerCnt; i++){
		float tmpWidth = 1;//临时添加
		int flag = 0;
		int currX = xID[verList[i]];
		int currY = yID[verList[i]];
		int id = currY*w + currX;
		float th = theta[id];
		dis = 0;

		int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
		if (theta[id] < -7 * PI / 8){
			offsetId = 7;
		}
		int x = currX;
		int y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNx[offsetId];
			y += nbNy[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h) break;

			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis * xDis + yDis * yDis);				
				dis += euDis;
				flag++;
				break;
			}
		}
		x = currX;
		y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNxarr[offsetId];
			y += nbNyarr[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h){
				break;
			}
			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis* xDis + yDis*yDis);			
				dis += euDis;
				flag++;
				break;
			}
		}

		if (flag == 2){
			initWidth[i] = dis;
		}else{
			initWidth[i] = 1;
		}		
	}


	float frontSum = 0;
	float backSum = 0;
	for (int j = 0; j <= range; j++){
		frontSum += initWidth[j];
	}
	for (int j = pathVerCnt - 1; j >= pathVerCnt - range - 1; j--){
		backSum += initWidth[j];
	}
	for (int i = 0; i < pathVerCnt; i++){
		if (i <= (range/2)){
			rangeWidth[i] = frontSum / (range + 1);
		}else if (i >= pathVerCnt - (range / 2 + 1)){
			rangeWidth[i] = backSum / (range + 1);
		}
		else {
			float tmpSum = 0;
			for (int j = i - (range / 2); j <= (range / 2 + i); j++){
				tmpSum += initWidth[j];
			}
			rangeWidth[i] = tmpSum / (range + 1);
		}	
	}
	memcpy(initWidth, rangeWidth, sizeof(float)*pathVerCnt);
	sort(rangeWidth, rangeWidth + pathVerCnt);
	maxWidth = rangeWidth[pathVerCnt - 1];
	std::cout << "裂缝的最大宽度为：" << maxWidth << endl;
	std::cout << "最宽处的坐标为：" << endl;
	int m = 1;
	for (int i = 0; i < pathVerCnt; i++){
		if (fabs(rangeWidth[pathVerCnt - 1] - initWidth[i])<=0.01){
			std::cout << m << "[" << xID[verList[i]] << "," << yID[verList[i]] << "]" << endl;
			m++;
		}
	}	
	
	delete[] initWidth;
	delete[] rangeWidth;
	return maxWidth;
}
float getWidth3(int* xID, int* yID, int* verList, int pathVerCnt, FImage& theta, FImage& peakFlag){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int nbNyarr[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int extN = 10;
	int cnt = 0;
	float maxWidth = 0;//临时添加
	int maxCnt = 0;
	float dis;
	float*  initWidth = new float[w*h];
	float*  rangeWidth = new float[w*h];
	cv::Mat verImg(h, w, CV_8UC1);
	memset(verImg.data, 0, verImg.rows*verImg.step);
	for (int i = 0; i < pathVerCnt; i++){
		verImg.at<char>(yID[verList[i]], xID[verList[i]]) = 255;
	}
	cv::imshow("verImg", verImg);
	cv::waitKey();
	int range = 6;//若range=20,即每个点的宽度为其左边10个、右边10个，及该点宽度之和再取平均值
	//int pointY = 369;  int pointX = 19;
	//int pointY = 459;  int pointX = 19;
	//int pointY = 164;  int pointX = 551;
	//int pointY = 301;  int pointX = 98;
	int pointY = 367;  int pointX = 153;
	for (int i = 0; i < pathVerCnt; i++){
		float tmpWidth = 1;//临时添加
		int flag = 0;
		int currX = xID[verList[i]];
		int currY = yID[verList[i]];
		int id = currY*w + currX;
		float th = theta[id];
		dis = 0;

		int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
		if (theta[id] < -7 * PI / 8){
			offsetId = 7;
		}
		int x = currX;
		int y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNx[offsetId];
			y += nbNy[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h) break;

			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis * xDis + yDis * yDis);
				dis += euDis;
				flag++;
				break;
			}
		}
		x = currX;
		y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNxarr[offsetId];
			y += nbNyarr[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h){
				break;
			}
			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis* xDis + yDis*yDis);
				dis += euDis;
				flag++;
				break;
			}
		}

		if (flag == 2){
			initWidth[i] = dis;
		}
		else{
			initWidth[i] = 1;
		}
	}


	float frontSum = 0;
	float backSum = 0;
	for (int j = 0; j <= range; j++){
		frontSum += initWidth[j];
	}
	for (int j = pathVerCnt - 1; j >= pathVerCnt - range - 1; j--){
		backSum += initWidth[j];
	}
	for (int i = 0; i < pathVerCnt; i++){
		if (i <= (range / 2)){
			rangeWidth[i] = frontSum / (range + 1);
		}
		else if (i >= pathVerCnt - (range / 2 + 1)){
			rangeWidth[i] = backSum / (range + 1);
		}
		else {
			float tmpSum = 0;
			for (int j = i - (range / 2); j <= (range / 2 + i); j++){
				tmpSum += initWidth[j];
			}
			rangeWidth[i] = tmpSum / (range + 1);
		}
	}
	//memcpy(initWidth, rangeWidth, sizeof(float)*pathVerCnt);
	//sort(rangeWidth, rangeWidth + pathVerCnt);
	int match = 0;
	maxWidth = 0;
	int maxXloc=0, maxYloc=0;
	float disThresh = 100;
	for (int i = 0; i < pathVerCnt; i++){
		int currx = xID[verList[i]];
		int curry = yID[verList[i]];
		int xDis = abs(pointX - currx);
		int yDis = abs(pointY - curry);
		float realDis = sqrt(xDis*xDis + yDis*yDis);
		if (realDis<=disThresh){
			float tmpWidth = rangeWidth[i];
			if (tmpWidth > maxWidth){
				match++;
				maxWidth = tmpWidth;
				maxXloc = currx;
				maxYloc = curry;
			}
		}
	}
	//maxWidth = rangeWidth[pathVerCnt - 1];
	std::cout << "裂缝的最大宽度为：" << maxWidth << endl;
	std::cout << "最宽处的坐标为：Y=" <<maxYloc<<" X="<<maxXloc<< endl;
	std::wcout << "match的值为：" << match << endl;
	

	delete[] initWidth;
	delete[] rangeWidth;
	return maxWidth;
}
float getWidth4(int* xID, int* yID, int* verList, int pathVerCnt, FImage& theta, FImage& peakFlag){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int nbNyarr[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int extN = 10;
	int cnt = 0;
	float maxWidth = 0;//临时添加
	int maxCnt = 0;
	float dis;
	float*  initWidth = new float[w*h];
	float*  rangeWidth = new float[w*h];
	int crackPixCnt = 0;
	
	int range = 6;//若range=20,即每个点的宽度为其左边10个、右边10个，及该点宽度之和再取平均值
	cv::Mat crackImg(h, w, CV_8UC1);
	memset(crackImg.data, 0,crackImg.rows*crackImg.step);

	for (int j = 0; j <pathVerCnt-1; j++){
			int x1 = xID[verList[j]];
			int y1 = yID[verList[j]];
			int x2 = xID[verList[j + 1]];
			int y2 = yID[verList[j + 1]];
			crackImg.at<uchar>(y1, x1) = 255;
			crackImg.at<uchar>(y2, x2) = 255;
			cv::line(crackImg, cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(255));
	}

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (crackImg.at<uchar>(i, j) <= 128){
				continue;
			}
		float tmpWidth = 1;//临时添加
		int flag = 0;
		int currX = j;
		int currY = i;
		int id = currY*w + currX;
		float th = theta[id];
		dis = 0;

		int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
		if (theta[id] < -7 * PI / 8){
			offsetId = 7;
		}
		int x = currX;
		int y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNx[offsetId];
			y += nbNy[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h) break;

			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis * xDis + yDis * yDis);
				dis += euDis;
				flag++;
				break;
			}
		}
		x = currX;
		y = currY;
		for (int k = 0; k < extN; k++){
			x += nbNxarr[offsetId];
			y += nbNyarr[offsetId];
			if (x < 0 || x >= w || y < 0 || y >= h){
				break;
			}
			int nbId = y*w + x;
			if (peakFlag[nbId]){
				int xDis = abs(currX - x);
				int yDis = abs(currY - y);
				float euDis = sqrt(xDis* xDis + yDis*yDis);
				dis += euDis;
				flag++;
				break;
			}
		}

		if (flag == 2){
			initWidth[crackPixCnt] = dis;
			crackPixCnt++;
		}
		else{
			initWidth[crackPixCnt] = 1;
			crackPixCnt++;
		}
	  }
  }


	float frontSum = 0;
	float backSum = 0;
	for (int j = 0; j <= range; j++){
		frontSum += initWidth[j];
	}
	for (int j = crackPixCnt - 1; j >= crackPixCnt - range - 1; j--){
		backSum += initWidth[j];
	}
	for (int i = 0; i < crackPixCnt; i++){
		if (i <= (range / 2)){
			rangeWidth[i] = frontSum / (range + 1);
		}
		else if (i >= crackPixCnt - (range / 2 + 1)){
			rangeWidth[i] = backSum / (range + 1);
		}
		else {
			float tmpSum = 0;
			for (int j = i - (range / 2); j <= (range / 2 + i); j++){
				tmpSum += initWidth[j];
			}
			rangeWidth[i] = tmpSum / (range + 1);
		}
	}
	memcpy(initWidth, rangeWidth, sizeof(float)*crackPixCnt);
	sort(rangeWidth, rangeWidth +crackPixCnt);

	maxWidth = rangeWidth[crackPixCnt - 1];
	std::cout << "裂缝的最大宽度为：" << maxWidth << endl;
	std::cout << "最宽处的坐标为：" << endl;
	int m = 1;
	for (int i = 0; i < crackPixCnt; i++){
		if (fabs(rangeWidth[crackPixCnt - 1] - initWidth[i]) <= 0.01){
			std::cout << m << "[" << xID[verList[i]] << "," << yID[verList[i]] << "]" << endl;
			m++;
		}
	}

	delete[] initWidth;
	delete[] rangeWidth;
	return maxWidth;
}
float getWidth5(int* xID, int* yID, int* verList, int pathVerCnt, FImage& theta, FImage& peakFlag){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int nbNyarr[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int extN = 10;
	int cnt = 0;
	float maxWidth = 0;//临时添加
	int maxCnt = 0;
	float dis;
	float*  initWidth = new float[w*h];
	float*  rangeWidth = new float[w*h];
	int crackPixCnt = 0;
	int range = 6;//若range=20,即每个点的宽度为其左边10个、右边10个，及该点宽度之和再取平均值
	//int pointX = 369;  int pointY = 19;
	//int pointX = 459;  int pointY = 19;
	//int pointX = 164;  int pointY = 551;
	//int pointX = 301;  int pointY = 98;
	int pointX = 367;  int pointY = 153;
	cv::Mat crackImg(h, w, CV_8UC1);
	memset(crackImg.data, 0, crackImg.rows*crackImg.step);

	for (int j = 0; j <pathVerCnt - 1; j++){
		int x1 = xID[verList[j]];
		int y1 = yID[verList[j]];
		int x2 = xID[verList[j + 1]];
		int y2 = yID[verList[j + 1]];
		crackImg.at<uchar>(y1, x1) = 255;
		crackImg.at<uchar>(y2, x2) = 255;
		cv::line(crackImg, cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(255));
	}

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (crackImg.at<uchar>(i, j) <= 128){
				continue;
			}
			float tmpWidth = 1;//临时添加
			int flag = 0;
			int currX = j;
			int currY = i;
			int id = currY*w + currX;
			float th = theta[id];
			dis = 0;

			int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
			if (theta[id] < -7 * PI / 8){
				offsetId = 7;
			}
			int x = currX;
			int y = currY;
			for (int k = 0; k < extN; k++){
				x += nbNx[offsetId];
				y += nbNy[offsetId];
				if (x < 0 || x >= w || y < 0 || y >= h) break;

				int nbId = y*w + x;
				if (peakFlag[nbId]){
					int xDis = abs(currX - x);
					int yDis = abs(currY - y);
					float euDis = sqrt(xDis * xDis + yDis * yDis);
					dis += euDis;
					flag++;
					break;
				}
			}
			x = currX;
			y = currY;
			for (int k = 0; k < extN; k++){
				x += nbNxarr[offsetId];
				y += nbNyarr[offsetId];
				if (x < 0 || x >= w || y < 0 || y >= h){
					break;
				}
				int nbId = y*w + x;
				if (peakFlag[nbId]){
					int xDis = abs(currX - x);
					int yDis = abs(currY - y);
					float euDis = sqrt(xDis* xDis + yDis*yDis);
					dis += euDis;
					flag++;
					break;
				}
			}

			if (flag == 2){
				initWidth[crackPixCnt] = dis;
				crackPixCnt++;
			}
			else{
				initWidth[crackPixCnt] = 1;
				crackPixCnt++;
			}
		}
	}


	float frontSum = 0;
	float backSum = 0;
	for (int j = 0; j <= range; j++){
		frontSum += initWidth[j];
	}
	for (int j = crackPixCnt - 1; j >= crackPixCnt - range - 1; j--){
		backSum += initWidth[j];
	}
	for (int i = 0; i < crackPixCnt; i++){
		if (i <= (range / 2)){
			rangeWidth[i] = frontSum / (range + 1);
		}
		else if (i >= crackPixCnt - (range / 2 + 1)){
			rangeWidth[i] = backSum / (range + 1);
		}
		else {
			float tmpSum = 0;
			for (int j = i - (range / 2); j <= (range / 2 + i); j++){
				tmpSum += initWidth[j];
			}
			rangeWidth[i] = tmpSum / (range + 1);
		}
	}
	memcpy(initWidth, rangeWidth, sizeof(float)*crackPixCnt);
	sort(rangeWidth, rangeWidth + crackPixCnt);

	int match = 0;
	maxWidth = 0;
	int maxXloc = 0, maxYloc = 0;
	float disThresh =10;
	int rangeWidthCnt = 0;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (crackImg.at<uchar>(i, j) < 128){
				continue;
			}
			int currx = j;
			int curry = i;
			int xDis = abs(pointX - currx);
			int yDis = abs(pointY - curry);
			float realDis = sqrt(xDis*xDis + yDis*yDis);
			if (realDis <= disThresh){
				float tmpWidth = rangeWidth[rangeWidthCnt];
				if (tmpWidth > maxWidth){
					match++;
					maxWidth = tmpWidth;
					maxXloc = currx;
					maxYloc = curry;
				}
			}
			rangeWidthCnt++;
		}
	}
	
	//maxWidth = rangeWidth[pathVerCnt - 1];
	std::cout << "裂缝的最大宽度为：" << maxWidth << endl;
	std::cout << "最宽处的坐标为：X=" << maxXloc << " Y=" << maxYloc << endl;
	std::wcout << "match的值为：" << match << endl;

	delete[] initWidth;
	delete[] rangeWidth;
	return maxWidth;
}

float getWidth6(int* xID, int* yID, int* verList, int pathVerCnt,
				FImage& theta, FImage& peakFlag,float& pixSize,
				int& widthAverage,float& maxWidth,float& width){

	int w = peakFlag.width();
	int h = peakFlag.height();
	float widthSum = 0;
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int nbNxarr[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int nbNyarr[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int extN = 10;
	int cnt = 0;
	//float maxWidth = 0;//临时添加
	int maxCnt = 0;
	float dis;
	float*  initWidth = new float[w*h];
	float*  rangeWidth = new float[w*h];
	int crackPixCnt = 0;
	int range = widthAverage;//range的默认值是6
	//int range = 6;//若range=20,即每个点的宽度为其左边10个、右边10个，及该点宽度之和再取平均值
	cv::Mat crackImg(h, w, CV_8UC1);
	memset(crackImg.data, 0, crackImg.rows*crackImg.step);

	for (int j = 0; j <pathVerCnt - 1; j++){
		int x1 = xID[verList[j]];
		int y1 = yID[verList[j]];
		int x2 = xID[verList[j + 1]];
		int y2 = yID[verList[j + 1]];
		crackImg.at<uchar>(y1, x1) = 255;
		crackImg.at<uchar>(y2, x2) = 255;
		cv::line(crackImg, cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(255));
	}

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (crackImg.at<uchar>(i, j) <= 128){
				continue;
			}
			float tmpWidth = 1;//临时添加
			int flag = 0;
			int currX = j;
			int currY = i;
			int id = currY*w + currX;
			float th = theta[id];
			dis = 0;

			int offsetId = (theta[id] + PI - PI / 8) / (PI / 4);
			if (theta[id] < -7 * PI / 8){
				offsetId = 7;
			}
			int x = currX;
			int y = currY;
			for (int k = 0; k < extN; k++){
				x += nbNx[offsetId];
				y += nbNy[offsetId];
				if (x < 0 || x >= w || y < 0 || y >= h) break;

				int nbId = y*w + x;
				if (peakFlag[nbId]){
					int xDis = abs(currX - x);
					int yDis = abs(currY - y);
					float euDis = sqrt(xDis * xDis + yDis * yDis);
					dis += euDis;
					flag++;
					break;
				}
			}
			x = currX;
			y = currY;
			for (int k = 0; k < extN; k++){
				x += nbNxarr[offsetId];
				y += nbNyarr[offsetId];
				if (x < 0 || x >= w || y < 0 || y >= h){
					break;
				}
				int nbId = y*w + x;
				if (peakFlag[nbId]){
					int xDis = abs(currX - x);
					int yDis = abs(currY - y);
					float euDis = sqrt(xDis* xDis + yDis*yDis);
					dis += euDis;
					flag++;
					break;
				}
			}

			if (flag == 2){
				initWidth[crackPixCnt] = dis;
				crackPixCnt++;
			}
			else{
				initWidth[crackPixCnt] = 1;
				crackPixCnt++;
			}
		}
	}


	float frontSum = 0;
	float backSum = 0;
	for (int j = 0; j <= range; j++){
		frontSum += initWidth[j];
	}
	for (int j = crackPixCnt - 1; j >= crackPixCnt - range - 1; j--){
		backSum += initWidth[j];
	}
	for (int i = 0; i < crackPixCnt; i++){
		if (i <= (range / 2)){
			rangeWidth[i] = frontSum / (range + 1);
		}
		else if (i >= crackPixCnt - (range / 2 + 1)){
			rangeWidth[i] = backSum / (range + 1);
		}
		else {
			float tmpSum = 0;
			for (int j = i - (range / 2); j <= (range / 2 + i); j++){
				tmpSum += initWidth[j];
			}
			rangeWidth[i] = tmpSum / (range + 1);
		}
	}
	memcpy(initWidth, rangeWidth, sizeof(float)*crackPixCnt);
	sort(rangeWidth, rangeWidth + crackPixCnt);

	maxWidth = rangeWidth[crackPixCnt - 1]*pixSize;
	float total = 0;
	for (int i = 0; i < crackPixCnt; i++){
		total = total + rangeWidth[i];
	}
	width = total / crackPixCnt*pixSize;
	/*std::cout << "裂缝的最大宽度为：" << maxWidth << endl;
	std::cout << "最宽处的坐标为：" << endl;
	int m = 1;
	for (int i = 0; i < crackPixCnt; i++){
		if (fabs(rangeWidth[crackPixCnt - 1] - initWidth[i]) <= 0.01){
			std::cout << m << "[" << xID[verList[i]] << "," << yID[verList[i]] << "]" << endl;
			m++;
		}
	}*/

	delete[] initWidth;
	delete[] rangeWidth;
	return width;
}



int getLongestPath1(FImage& gapImg, CMst& outTree,FImage& theta, FImage& peakFlag,
					CrackInfor* crackStore,cv::Mat& src_image,cv::Mat& outCrackImg,
					float& crackDis,float& crackLength,float& pixSize,int& widthAverage){
	int w = gapImg.width();
	int h = gapImg.height();
	int* xID = new int[w*h];
	int* yID =new int[w*h];
	int* root = new int[w*h];
	int* leaf = new int[w*h];
	int* curVer = new int[w*h];//当前根节点代表的树的顶点总数
	int* visited = new int[w*h];
	int* verList = new int[w*h];
	float* disList = new float[w*h];
	float* tmpDisList = new float[w*h];
	int* cuttedVer = new int[w*h];
	int cuttedVerCnt = 0;
	int cnt = 0;
	int crackNum = 0;
	//double pixSize =  getmmperpixle(1250, src_image);
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			int id = i*w + j;
			if(gapImg[id] > 0.00){
				xID[cnt] = j;
				yID[cnt] = i;
				cnt++;
			}
		}
	}
	
	int rootCnt = 0;
	root[rootCnt] = 0;
	rootCnt++;
	int numV = cnt;
	printf("cnt:%d\n", cnt);
	for(int i = 0; i < numV; i++){
		if(outTree.ParentDistance(i) > crackDis){
			//crackDis的默认值是0.18
			root[rootCnt] = i;
			rootCnt++;
		}
	}
	printf("rootCnt  1  :%d\n",rootCnt);

	int total = 0;//检验将一棵树裁剪后，是否正确
	//cv::Mat outCrackImg(h, w, CV_32FC1);
	memset(outCrackImg.data, 0, outCrackImg.rows*outCrackImg.step);
	for(int i = 0; i < rootCnt; i++){

		int  curVerCnt = 0;  //当前树初始化
		curVer[curVerCnt] = root[i];
		curVerCnt++;

		for(int c = 0; c < curVerCnt; c++){
			int tmp = curVer[c];
			int m = outTree.ChildNum(tmp);
			for(int n = 0; n < m; n++){
				if(isCut(root, rootCnt, outTree.ChildIndex(tmp)[n]))
					continue;
				curVer[curVerCnt] = outTree.ChildIndex(tmp)[n];
				curVerCnt++;
				
			}
		}
		//printf("cruVer:%d  ",curVerCnt);


		//计算每一棵树里面的叶子个数
		int leafCnt = 0;
		for(int j = 0; j < curVerCnt; j++){
			if(outTree.ChildNum(curVer[j]) == 0){
				leaf[leafCnt] = curVer[j];
				leafCnt++;
			}
			else{
				int m = outTree.ChildNum(curVer[j]);
				int cutNum = 0;
				for(int c = 0; c < m; c++){
					if(isCut(root, rootCnt, outTree.ChildIndex(curVer[j])[c]))
						cutNum++;				
				}
				if(cutNum == m){
					leaf[leafCnt] = curVer[j];
					leafCnt++;
				} 
				if(cutNum == m-1){
					if(curVer[j] == root[i]){
						leaf[leafCnt] = curVer[j];
						leafCnt++;
					}
				}
			}
		}
		//printf("leanfCnt:%d    ",leafCnt);
		total+= curVerCnt;
		float endLength = 10;
		//利用广度搜索，开始寻找最长路径

		int oneVer;
		int theOtherVer;
		//crackLength的默认值是0.7
	while(endLength >= crackLength){
		float pathLength = 0;
		for(int j = 0; j < leafCnt; j++){

			if(isInsideTree(cuttedVer,cuttedVerCnt,leaf[j])){
				continue;
			}
			//printf("the leaf is: %d\n",leaf[j]);
			float curLength;
			memset(visited, 0, sizeof(int)*w*h);
			int pathVerNum = getPathNum(leaf[j],curVer,curVerCnt,visited,verList,disList,tmpDisList,curLength,cuttedVer,cuttedVerCnt,outTree); 
			if(pathVerNum == -1)
				printf("error!!!!!\n");
		//	printf("curLength: %f\n",curLength);

			if(curLength >= pathLength){
				oneVer = leaf[j];
				theOtherVer = pathVerNum;
				pathLength = curLength;
			}
		}
		endLength = pathLength;
		//利用深度搜索，根据两点得到路径信息
		memset(visited, 0, sizeof(int)*w*h);
		int pathVerCnt = 0;//路径顶点的个数
		pathVerCnt = getPathVer(oneVer,theOtherVer,curVer,curVerCnt,visited,verList,outTree);
		//std::cout<<"the pathVerCnt is:"<<pathVerCnt<<std::endl;
		
		if(pathLength > crackLength){
			cv::Mat crackIndexImg(h, w, CV_8UC1);
			memset(crackIndexImg.data, 0, crackIndexImg.rows*crackIndexImg.step);
			//printf("the *********length ******of the crack is: -----------%f\n", pathLength);
			std::cout<<"the pathVerCnt is:"<<pathVerCnt<<std::endl;
			for(int j = 0; j < pathVerCnt - 1; j++){
				int x1 = xID[verList[j]];
				int y1 = yID[verList[j]];
				int x2 = xID[verList[j + 1]];
				int y2 = yID[verList[j + 1]];
				//crackStore[crackNum].vertexIdx[j] = xID[verList[j]];
				//crackStore[crackNum].vertexIdy[j] = yID[verList[j]];
				cuttedVer[cuttedVerCnt] = verList[j];
				cuttedVerCnt++;
				outCrackImg.at<uchar>(y1, x1) = 255;
				outCrackImg.at<uchar>(y2, x2) = 255;
				cv::line(outCrackImg,cvPoint(x1,y1),cvPoint(x2,y2),cvScalar(255));

				crackIndexImg.at<uchar>(y1, x1) = 255;
				crackIndexImg.at<uchar>(y2, x2) = 255;
				cv::line(crackIndexImg, cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(255));
			}
			//crackStore[crackNum].vertexIdx[pathVerCnt - 1] = xID[verList[pathVerCnt - 1]];
			//crackStore[crackNum].vertexIdy[pathVerCnt - 1] = yID[verList[pathVerCnt - 1]];
			cuttedVer[cuttedVerCnt] = verList[pathVerCnt - 1];
			cuttedVerCnt++;
			cv::imshow("crackIndexImg1", crackIndexImg);
			int crackIndexCnt = 0;
			for (int p = 0; p < h; p++){
				for (int q = 0; q < w; q++){
					if (crackIndexImg.at<uchar>(p, q)>128){
						crackStore[crackNum].vertexIdx[crackIndexCnt] = q;
						crackStore[crackNum].vertexIdy[crackIndexCnt] = p;
						crackIndexCnt++;
					}
				}
			}
			/*for (int r = 0; r < crackIndexCnt; r++){
				int a = crackStore[crackNum].vertexIdy[crackIndexCnt];
				int b = crackStore[crackNum].vertexIdx[crackIndexCnt];
				crackIndexImg.at<uchar>(a,b)= 255;
			}
			cv::imshow("crackIndexImgStore", crackIndexImg);*/
			//verList[]中存储的是种子点，并非裂缝上的所有点
			//得到像素宽度，再乘以每个像素的尺寸
			printf("the *********length ******of the crack is: -----------%d\n", pathVerCnt);
			float _maxWidth, _width;
			double width = getWidth6(xID, yID,verList,pathVerCnt,theta, peakFlag,
				pixSize,widthAverage,_maxWidth,_width);
				//width = width * getmmperpixle(1382.0, src_image);
				//width = width * pixSize;
			cout << "宽度的值是--------**********" << _width << "  "<<_maxWidth << endl;

			//crackStore[crackNum].width = width;
			crackStore[crackNum].vertexNum = crackIndexCnt;
			crackStore[crackNum].length = crackIndexCnt;
			crackStore[crackNum].width = _width;
			crackStore[crackNum].maxWidth = _maxWidth;
			//cout<<"the width of the crack is:"<<width<<endl;
			crackNum++;
			}
		}
	printf("root 节点运行完一次\n");
		
	}///////////
	printf("rootCnt  2  :%d\n",rootCnt);
	cv::imshow("outCrackImg",outCrackImg);
	//cv::imwrite("outCrakImg.jpg",outCrackImg);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\temp\\10.outCrack.png",outCrackImg);
	cv::imwrite("0001_0600_0000.png", outCrackImg);
	
	//printf("total:%d\n",total);
	delete[] cuttedVer;
	delete[] tmpDisList;
	delete[] verList;
	delete[] disList;
	delete[] visited;
	delete[] curVer;
	delete[] xID;
	delete[] yID;
	delete[] leaf;
	delete[] root;
	return crackNum;
}

//首先对图像对outCrack,gtImgPix,gtImgWidth进行二值化处理，得到的图像裂缝像素点为1，背景像素点为0
//输入的带宽度的gtImg的背景为0，裂缝为1，不带宽度的相反
void initGTImg(cv::Mat& gtWidthImg, cv::Mat& gtPixImg){
	cv::Mat destWidthImg, destPixImg;
	cv::Mat grayWidthImg, grayPixImg;
	//cv::resize(gtWidthImg, destWidthImg, cv::Size(gtWidthImg.cols / 4, gtWidthImg.rows/ 4));
	//cv::resize(gtPixImg, destPixImg, cv::Size(gtPixImg.cols/ 4, gtPixImg.rows/ 4));
	//cvtColor(destWidthImg, grayWidthImg, CV_BGR2GRAY);
	cvtColor(gtPixImg, grayPixImg, CV_BGR2GRAY);
	/*int h = gtWidthImg.rows;
	int w = gtWidthImg.cols;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (gtPixImg.at<uchar>(i, j) != 0){
				gtPixImg.at<uchar>(i, j) =  0;
			}
			else{
				gtPixImg.at<uchar>(i,j) = 1;
			}
		}
	}
	cv::imshow("gtPixImg", gtPixImg);
	cv::imshow("gtWidthImg", gtWidthImg);
	cv::imwrite("D:\\BridgeProject\\ImgWrite\\performanceTest\\gtPixImg\\gtPixImg1.jpg", gtPixImg);
	cv::imwrite("D:\\BridgeProject\\ImgWrite\\performanceTest\\gtWidthImg\\gtWidthImg1.jpg", gtWidthImg);*/
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\performanceTest\\grayPixImg\\grayPixImg1.jpg",grayPixImg);
	int h = grayPixImg.rows;
	int w = grayPixImg.cols;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (((int)grayPixImg.at<uchar>(i, j)) != 0){
				grayPixImg.at<uchar>(i, j) = 1;
			}
			else{
				grayPixImg.at<uchar>(i, j) = 0;
			}

			if (((int)gtWidthImg.at<uchar>(i, j)) == 0){
				gtWidthImg.at<uchar>(i, j) = 0;
			}
			else{
				gtWidthImg.at<uchar>(i, j) = 1;
			}
		}
	}
	cv::imshow("gtPixImg", grayPixImg);
	cv::imshow("gtWidthImg", gtWidthImg);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\performanceTest\\gtPixImg\\gtPixImg1.jpg", grayPixImg);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\performanceTest\\gtWidthImg\\gtWidthImg1.jpg", gtWidthImg);
	
}
//得到图像检测结果对比ground truth的正确率等参数,对像素的相对位置进行对比，得到指标
//cv::Mat& gtImg, 输入三幅图像的裂缝像素点不等于0，背景像素点为0
//输入的图像为单像素groundtruth，带宽度groundtruth,检测到的裂缝图像
void getPixelPerformance1(cv::Mat& gtImgWidth, cv::Mat& gtImgPix, cv::Mat& outCrackImg){
	int h = outCrackImg.rows;
	int w = outCrackImg.cols;
	int gtImgPixCnt = 0;
	int gtImgWidthCnt = 0;
	int outCrackImgCnt = 0;
	/*int* gtImgWidthLoc = new int[w*h];
	int* outCrackImgLoc = new int[w*h];*/
	int tp = 0;//正确检测到的像素
	int fp = 0;//错误检测到的像素点
	int fn = 0;//漏检的像素点
	int tn = 0;//正确检测到的背景像素点个数，未参与运算
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (outCrackImg.at<uchar>(i, j) != 0){
				/*outCrackImgLoc[outCrackImgCnt] = i*w+j;*/
				outCrackImgCnt++;
			}
			if (outCrackImg.at<uchar>(i, j) != 0 && gtImgWidth.at<uchar>(i, j) != 0){
				tp++;
			}
			/*if (gtImgWidth.at<uchar>(i, j) != 0){
				gtImgWidthLoc[gtImgWidthCnt] = i*w+j;
				gtImgWidthCnt++;
			}*/
			if (gtImgPix.at<uchar>(i, j) != 0){
				gtImgPixCnt++;
			}
		}
	}

	/*for (int i = 0; i < outCrackImgCnt; i++){
		for (int j = 0; j < gtImgWidthCnt; j++){
			if (outCrackImgLoc[i] == gtImgWidthLoc[j]){
				tp++;
				break;
			}
		}
	}*/

	fp = outCrackImgCnt - tp;
	fn = gtImgPixCnt - tp;


	float p = tp / (tp + fp);//准确度
	float s = tp / (tp + fn);//敏感度
	float dsc = 2 * tp / (2 * tp + fp + fn);//调和平均数

	std::cout << "getPixelNPerformance1" << endl;
	std::cout << "p的值为" << p << endl;
	std::cout << "s的值为" << s << endl;
	std::cout << "dsc的值为" << dsc << endl;

	/*delete outCrackImgLoc;
	delete gtImgWidthLoc;*/
}


//在outCrackImg的（i,j)点N*N范围内是否有不为零的像素点
 bool existNotZero(cv::Mat& outCrackImg, int i, int j, int N){
	 int h = outCrackImg.rows;
	 int w = outCrackImg.cols;
	 bool exist = false;//是否存在非0值，即是否存在检测到的裂缝
	 int NleftUp = (N - 1) / 2;
	 int NrightDown = (N - 1) - (N - 1) / 2;
	
	 for (int m = i - NleftUp; m <= i + NrightDown; m++){
		 for (int n = j - NleftUp; n <= j + NrightDown; n++){
			 if (m < 0 || m >= h || n < 0 || n >= w){
				 continue;
			 }
			 if (outCrackImg.at<uchar>(m, n) != 0){
				 exist= true;
				 break;
			 }
		 }
		 if (exist){
			 break;
		 }
	 }
	 return exist;

}
//图像检测结果outCrackImg和ground truth进行对比的像素个数统计结果
//在ground truth一定范围N*N内寻找是否有检测到的裂缝像素,得到指标
void getPixelPerformanceN(cv::Mat& gtImg, cv::Mat& outCrackImg){
	int h = outCrackImg.rows;
	int w = outCrackImg.cols;
	int gtData = 0;
	int outCrackData = 0;
	int tp = 0;
	int fp = 0;
	int fn = 0;
	int tn = 0;
	int gtAmount = 0;
	int outCrackAmount = 0;
	bool exist = false;
	int N = 3;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			gtData = gtImg.at<uchar>(i, j);
			outCrackData = outCrackImg.at<uchar>(i, j);
			if (gtData == 0 && outCrackData == 0){
				tn++;
				continue;
			}
			else if (gtData == 0 && outCrackData != 0){
				fp++;
			}
			else{
				exist = existNotZero(outCrackImg, i, j, N);
				if (exist){
					tp++;					
				}
				else{
					fn++;					
				}
			}
		
		}
	}

	float p = tp / (tp + fp);//准确度
	float s = tp / (tp + fn);//敏感度
	float dsc = 2 * tp / (2 * tp + fp + fn);//调和平均数
	std::cout << "getPixelPerformanceN" << endl;
	std::cout << "p的值为" << p << endl;
	std::cout << "s的值为" << s << endl;
	std::cout << "dsc的值为" << dsc << endl;
}
//计算outCrackImg和groung truth的长度，并对比，长度计算方法为像素点的总数
void getLengthPerformance(cv::Mat& gtImgPix, cv::Mat& gtImgWidth,cv::Mat& outCrackImg){
	int h = outCrackImg.rows;
	int w = outCrackImg.cols;
	int gtImgPixCnt = 0;
	int gtImgWidthCnt = 0;
	int outCrackImgCnt = 0;
	int* gtImgWidthLoc = new int[w*h];
	int* outCrackImgLoc = new int[w*h];
	int tp = 0;//正确检测到的像素
	int fp = 0;//错误检测到的像素点
	int fn = 0;//漏检的像素点
	int tn = 0;//正确检测到的背景像素点个数，未参与运算
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (outCrackImg.at<uchar>(i, j) != 0){
				outCrackImgLoc[outCrackImgCnt] = i*w + j;
				outCrackImgCnt++;
			}
			if (gtImgWidth.at<uchar>(i, j) != 0){
				gtImgWidthLoc[gtImgWidthCnt] = i*w + j;
				gtImgWidthCnt++;
			}
			if (gtImgPix.at<uchar>(i, j) != 0){
				gtImgPixCnt++;
			}
		}
	}


	for (int i = 0; i < outCrackImgCnt; i++){
		for (int j = 0; j < gtImgWidthCnt; j++){
			if (outCrackImgLoc[i] == gtImgWidthLoc[j]){
				tp++;
				break;
			}
		}
	}

	fp = outCrackImgCnt - tp;
	fn = gtImgPixCnt - tp;

	float cpt = tp / gtImgPixCnt;
	float crt = tp / outCrackImgCnt;
	float f = 2 * cpt*crt / (cpt + crt);

	std::cout << "getLengthPerformanceN" << endl;
	std::cout << "cpt的值为" << cpt<< endl;
	std::cout << "crt的值为" << crt << endl;
	std::cout << "f的值为" << f << endl;

}
//通过hausdorff距离判断裂缝检测性能
float getHausdorff(cv::Mat& gtImg, cv::Mat& outCrackImg){
	int h = outCrackImg.rows;
	int w = outCrackImg.cols;
	int* gtXid = new int[h*w];
	int* gtYid = new int[h*w];
	int* outXid = new int[h*w];
	int* outYid = new int[h*w];
	int L = 8;//根据像素的宽度取，如果裂缝宽度为3像素，则可取值5
	int gtCnt = 0;
	int outCnt = 0;
	int gtData = 0;
	int outCrackData = 0;
	float minDis = std::sqrt(h*h + w*w);
	float maxValue = 0;
	float tmpDis = 0;
	int xDis = 0;
	int yDis = 0;
	for(int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			gtData = gtImg.at<uchar>(i, j);
			outCrackData = outCrackImg.at<uchar>(i, j);
			if (gtData != 0){
				gtXid[gtCnt] = j;
				gtYid[gtCnt] = i;
				gtCnt++;
			}
			if (outCrackData != 0){
				outXid[outCnt] = j;
				outYid[outCnt] = i;
				outCnt++;
			}
		}
	}
	//得到h(outCrackImg,gtImg)的值，即outCrackImg所有点到gtImg的最小距离里面的最大值
	for (int i = 0; i < outCnt; i++){
		for (int j = 0; j < gtCnt; j++){
			xDis = outXid[i] - gtXid[j];
			yDis = outYid[i] - gtYid[j];
			tmpDis = std::sqrt(xDis*xDis + yDis*yDis);
			if (tmpDis < minDis){
				minDis = tmpDis;
			}
		}
		if (minDis > maxValue){
			maxValue = minDis;
		}
	}
	float max1 = maxValue;


	maxValue = 0;
	minDis = std::sqrt(h*h + w*w);
	tmpDis = 0;


	//得到h(gtImg,outCrackImg)的值，即gtImg所有点到outCrackImg的最小距离里面的最大值
	for (int i = 0; i < gtCnt; i++){
		for (int j = 0; j < outCnt; j++){
			xDis = outXid[i] - gtXid[j];
			yDis = outYid[i] - gtYid[j];
			tmpDis = std::sqrt(xDis*xDis + yDis*yDis);
			if (tmpDis < minDis){
				minDis = tmpDis;
			}
		}
		if (minDis > maxValue){
			maxValue = minDis;
		}
	}
	float max2 = maxValue;
	float hausDorffDis = (max1 > max2) ? max1 : max2;
	float SM = 100 - (hausDorffDis / L) * 100;	

	std::cout << "getHausdorff" << endl;
	std::cout << "SM的值为" << SM << endl;
	

	delete[] gtXid;
	delete[] gtYid;
	delete[] outXid;
	delete[] outYid;
	return SM;
}
 
// normal direction
void GetTheta(FImage& dx, FImage& dy, FImage& outTheta)
{
	int w = dx.width();
	int h = dx.height();
	outTheta.allocate(w, h);
	for (int i = 0; i < w*h; i++){
		outTheta[i] = atan2(dy[i], dx[i]); // -PI to PI
	}
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
	//printf("宽度 是%d，高度是%d",w,h);

	for (int i = 1; i < h-1; i++){
		for (int j = 1; j < w-1; j++){
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

/*
The equation for the decay of the field is
DF(s, k) = exp(-(s ^ 2 + c*k ^ 2) / sigma ^ 2)
where 's' is the length of the circle that joins
the two points, and 'k' is its curvature.

'sigma' control the scale of the voting field.
'c' control the ratio between distance and curvature.
The higher 'c' is, the narrower the field will be.
*/
float DF(float dx, float dy, float sigma)
{
	float th = abs(atan2(dy, dx));
	if (th > PI / 2) th = PI - th;

	float c = -16 * log(0.1)*(sigma - 1) / (PI*PI);
	//float c = 100 * sigma; // for test

	float L = sqrt(dx*dx + dy*dy);

	float s = L; // arc length
	if (abs(th) > FLT_EPSILON){
		s = L*th / sin(th);
	}

	float k = 0; // curvature
	if (abs(L) > FLT_EPSILON){
		k = 2 * sin(th) / L; 
	}

	float vt = exp(-(s*s + c*k*k) / (sigma*sigma));
	return vt;
}


// outTh is tangent vectors
void FindSeeds(FImage& peakFlag, FImage& deri, FImage& theta, FImage& outSeeds, FImage& outTh, FImage& widthImg)
{
	int w = peakFlag.width();
	int h = peakFlag.height();
	
	outSeeds.allocate(w, h);
	outTh.allocate(w, h);
	outSeeds.setValue(-1);
	outTh.setValue(-1);

	widthImg.allocate(w,h);
	widthImg.setValue(0);
	
	// normal directions
	int nbNx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
	int nbNy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
	int extN = 5;

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
						float response = __min(de, currDe);
						int cx = (float)(x + j) / 2 + 0.5;
						int cy = (float)(y + i) / 2 + 0.5;

						//widthImg[i*w +j] = max(abs(cx - j),abs(cy - i));
						widthImg[cy*w + cx] = __max(abs(cx - j),abs(cy - i));
						//if (response > 0.1)
						{
							outSeeds[cy*w + cx] = (de + currDe) / 2.;
							//outSeeds[cy*w + cx] = response;
							//outSeeds[idx] = 1;
							//outSeeds[tidx] = 1;

#if 0
							float tmpTh = currTh;
							if(tmpTh<0) tmpTh+=PI;
#else
							float tmpTh = PI - (currTh + th) / 2.; // change to tangent direction
							if (tmpTh < 0) tmpTh += PI;
							if (tmpTh > PI) tmpTh -= PI;
#endif
							outTh[cy*w + cx] = tmpTh; // 0 ~ PI
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

	showImg.imshow("Final Cracks", 0);
	//showImg.imshow("Final Cracks");
}
void CrackThresholding(FImage& voteMag, FImage& votePeak, FImage& outCrack, float minTh, float maxTh)
{
	int w = voteMag.width();
	int h = voteMag.height();
	outCrack.allocate(w, h);
	outCrack.setValue(-1);

	// add strong and weak cra ck ( if weak crack connects to any strong crack, add it)
	int currCrackID = 0;
	FImage visited(w, h);
	visited.setValue(0);
	const int dx8[8] = { -1, 0, 1, 0, -1, -1, 1, 1 };
	const int dy8[8] = { 0, -1, 0, 1, 1, -1, 1, -1 };
	int* xvec = new int[w*h];
	int* yvec = new int[w*h];
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int pixIdx = i*w + j;

			if (!votePeak[pixIdx]
				|| voteMag[pixIdx] < minTh
				|| visited[pixIdx]) continue;

			// start new region
			xvec[0] = j;
			yvec[0] = i;
			visited[pixIdx] = 1;
			int isAnyStrong = voteMag[pixIdx]>maxTh ? 1 : 0;
			int count = 1;
			for (int c = 0; c < count; c++){
				for (int n = 0; n < 8; n++){
					int x = xvec[c] + dx8[n];
					int y = yvec[c] + dy8[n];
					if ((x >= 0 && x < w) && (y >= 0 && y < h)){
						int nbIdx = y*w + x; // neighbor index

						if (!votePeak[nbIdx]
							|| voteMag[nbIdx] < minTh
							|| visited[nbIdx]) continue;

						if (voteMag[nbIdx] > maxTh){
							isAnyStrong = 1;
						}
						// add
						xvec[count] = x;
						yvec[count] = y;
						visited[nbIdx] = 1;
						count++;
					}
				}
			}
			//
			if (isAnyStrong){
				for (int k = 0; k < count; k++){
					int idx = yvec[k] * w + xvec[k];
					outCrack[idx] = currCrackID;
				}
			}
			//
			currCrackID++;
		}
	}
	delete[] xvec;
	delete[] yvec;
}



class CCrackDetection
{
public:
	CCrackDetection();
	~CCrackDetection();

	int Process(uchar* imgData, int dataLen);

	int GetCrackNumber();
	int GetCrackPostions(int crackIndex,int* outPos);
	double GetCrackWidth(int crackIndex);
	double GetCrackMaxWidth(int crackIndex);
	double GetCrackLength(int crackIndex);
	double GetCrackContrast(int crackIndex);
	int scale;//取整数，表示原图是resize()后的图像的scale倍
	int crackNum;
	int width ,height;
	float gauthSigma;//高斯滤波的参数
	float seedsRange;//寻找共生边缘时的搜索范围extN
	float crackDis;//从最小生成树上断开的两点距离
	float crackLength;//保留的裂缝的最小长度阈值
	float pixSize;//每个像素的尺寸
	float widthAverage;//计算每个种子点处宽度时取平均值的范围
	FImage contrastImg;

private:
	CrackInfor crackStore[100];
};

CCrackDetection::CCrackDetection()
{
	gauthSigma=2;//高斯滤波的参数
	seedsRange=5;//寻找共生边缘时的搜索范围extN
	crackDis=0.18;//从最小生成树上断开的两点距离
	crackLength=0.7;//保留的裂缝的最小长度阈值
	pixSize=0.075;//每个像素的尺寸，默认值是0.075mm
	widthAverage=6;//计算每个种子点处宽度时取平均值的范围
	scale = 4;
}

CCrackDetection::~CCrackDetection()
{

}

int CCrackDetection::Process(uchar* imgData, int dataLen)
{
	
	// Load image (jpg/png etc.) from memory using OpenCV
	std::vector<uchar> buff(dataLen);
	memcpy(&buff[0], imgData, dataLen);
	cv::Mat CVimg = cv::imdecode(cv::Mat(buff), CV_LOAD_IMAGE_UNCHANGED);
	//cv::imshow("cvimg",CVimg);
	//cv::waitKey();
	
	if (CVimg.data == NULL){
		printf("OpenCV load stream failed!\n");
		return 0;
		
	}
	cv::Mat grayImg,destImg;
	int scale = CCrackDetection::scale;
	cv::resize(CVimg, destImg,cv::Size(CVimg.cols/scale, CVimg.rows/scale));
	cvtColor(destImg, grayImg, CV_BGR2GRAY);
	//cvtColor(CVimg, grayImg, CV_BGR2GRAY);
	int w = grayImg.cols;
	int h = grayImg.rows;
	CCrackDetection::width = w*scale;
	CCrackDetection::height = h*scale;
	cv::imshow("grayImgshow", grayImg);
	//cv::imwrite("D:\\BridgeProject\\ImgWrite\\temp\\1.gray.jpg",grayImg);
	//FImage seeds;
	//getSeedsImg(grayImg, seeds);

	float gauthSigma=CCrackDetection::gauthSigma;//高斯滤波的参数
	int seedsRange = CCrackDetection::seedsRange;//寻找共生边缘时的搜索范围extN
	float crackDis = CCrackDetection::crackDis;//从最小生成树上断开的两点距离0.17
	float crackLength = CCrackDetection::crackLength;//保留的裂缝的最小长度阈值0.8
	float pixSize = CCrackDetection::pixSize;//计算宽度时的搜索范围10
	int widthAverage = CCrackDetection::widthAverage;//计算每个种子点处宽度时取平均值的范围6
	
	FImage contrastImg = CCrackDetection::contrastImg;
	FImage cracks, peakFlags, deri, theta;
	CrackPreDetection(grayImg, cracks, peakFlags, deri, theta,contrastImg,gauthSigma,seedsRange);
	CMst outTree;
	GenerateTree(cracks,outTree);
	
	CutToManyTree(cracks, outTree);
	//cv::Mat outCrackImg(h, w, CV_32FC1);
	cv::Mat outCrackImg(h, w, CV_8UC1);
	CCrackDetection::crackNum = getLongestPath1(cracks, outTree, theta, peakFlags,
								CCrackDetection::crackStore, CVimg, outCrackImg,
								crackDis,crackLength,pixSize,widthAverage);	
	//getPixelPerformanceN(outCrackImg,outCrackImg);
	//getLengthPerformanceN(outCrackImg, outCrackImg);
	//getLengthPerformance(outCrackImg, outCrackImg, outCrackImg);
	////cv::Mat gtWidthImg = cv::imread("D:\\BridgeProject\\partTest\\PerformaceTest\\gtWidthImg\\0U0A0087o.jpg");
	//cv::Mat gtPixImg = cv::imread("D:\\BridgeProject\\partTest\\PerformaceTest\\gtPixImg\\0U0A0087o.jpg");
	//initGTImg(gtWidthImg, gtPixImg);
	//getPixelPerformance1(gtWidthImg, gtPixImg, outCrackImg);
	//cv::waitKey();
	return 0;
}

int CCrackDetection::GetCrackNumber()
{
	return CCrackDetection::crackNum;
}

int CCrackDetection::GetCrackPostions(int crackIndex,int* outPos)
{
	int verNum = CCrackDetection::crackStore[crackIndex].vertexNum;
	for (int i = 0; i < verNum; i++){
		outPos[2 * i] = CCrackDetection::crackStore[crackIndex].vertexIdx[i];
		outPos[2 * i+1] = CCrackDetection::crackStore[crackIndex].vertexIdy[i];

	}
	return verNum;
	//int posNum = 0;
	//int posCnt = 0;
	//int verNum = CCrackDetection::crackStore[crackIndex].vertexNum;
	//std::cout<<"the verNum is "<<verNum<<std::endl;
	//int w = CCrackDetection::width;
	//int h = CCrackDetection::height;
	//cv::Mat crackImg(h, w, CV_8UC1);
	//std::cout<<"the width and the heiht is:"<<w<<"  "<<h<<std::endl;
	//memset(crackImg.data, 0, crackImg.rows*crackImg.step); 
	//for(int i = 0; i < verNum - 1; i++){
	//	//std::cout<<"the i is:"<<i<<std::endl;
	//	int x1 = CCrackDetection::crackStore[crackIndex].vertexIdx[i];
	//	int y1 = CCrackDetection::crackStore[crackIndex].vertexIdy[i];
	//	int x2 = CCrackDetection::crackStore[crackIndex].vertexIdx[i+1];
	//	int y2 = CCrackDetection::crackStore[crackIndex].vertexIdy[i+1];
	//	cv::line(crackImg,cvPoint(x1, y1),cvPoint(x2, y2),cvScalar(255));
	//}
	//
	////cv::imshow("crackIndex",crackImg);
	//cv::waitKey(0);
	//for(int i = 0; i < crackImg.rows; i++){
	//	//uchar* data = crackImg.ptr(j);
	//	for(int j = 0; j < crackImg.cols; j++){
	//		if(crackImg.at<uchar>(i,j) != 0){
	//			outPos[posCnt] = j;
	//			posCnt++;
	//			outPos[posCnt] = i;
	//			posCnt++;
	//		}
	//	}
	//}
	//posNum = (int)(posCnt / 2);
	////std::cout<<"the posNum is:"<<posNum<<std::endl;

	//return posNum;
}

double CCrackDetection::GetCrackWidth(int crackIndex)
{
	int scale = CCrackDetection::scale;
	return CCrackDetection::crackStore[crackIndex].width*scale;
}
double CCrackDetection::GetCrackMaxWidth(int crackIndex){
	int scale = CCrackDetection::scale;
	return CCrackDetection::crackStore[crackIndex].maxWidth*scale;
}

double CCrackDetection::GetCrackLength(int crackIndex)
{
	int scale = CCrackDetection::scale;
	int num = CCrackDetection::crackStore[crackIndex].vertexNum;
	float size = CCrackDetection::pixSize;
	return num*size*scale;
}
double CCrackDetection::GetCrackContrast(int crackIndex){
	//这个函数还没有实现，后面补充----------------------------------------
	return 0;
}


/************************************************************************/
/* EXTERNAL API                                                         */
/************************************************************************/
CRACK_API CRACK_DETECTOR_HANDLE CRACK_DETECTOR_Create()
{
	CCrackDetection* detector = new CCrackDetection();

	return (CRACK_DETECTOR_HANDLE)(detector);
}

CRACK_API int CRACK_DETECTOR_Destroy(CRACK_DETECTOR_HANDLE* hnd)
{
	if (*hnd){
		delete (CRACK_DETECTOR_HANDLE*)(*hnd);
		*hnd = NULL;
	}
	return 0;
}

CRACK_API int CRACK_DETECTOR_Process(CRACK_DETECTOR_HANDLE hnd, uchar* imgData, int dataLen)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->Process(imgData, dataLen);
	return 0;
}

CRACK_API int CRACK_DETECTOR_GetCrackNumber(CRACK_DETECTOR_HANDLE hnd)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	int num;
	num = detector->GetCrackNumber();
	return num;
}

CRACK_API double CRACK_DETECTOR_GetCrackWidth(CRACK_DETECTOR_HANDLE hnd, int crackIndex)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	double width = detector->GetCrackWidth(crackIndex);
	return width;
}

CRACK_API double CRACK_DETECTOR_GetCrackMaxWidth(CRACK_DETECTOR_HANDLE hnd, int crackIndex)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	return detector->GetCrackMaxWidth(crackIndex);
}
CRACK_API double CRACK_DETECTOR_GetCrackContrast(CRACK_DETECTOR_HANDLE hnd, int crackIndex)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	return detector->GetCrackContrast(crackIndex);
}

CRACK_API double CRACK_DETECTOR_GetCrackLength(CRACK_DETECTOR_HANDLE hnd, int crackIndex)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	double length = detector->GetCrackLength(crackIndex);
	return length;
}

CRACK_API int CRACK_DETECTOR_GetCrackPositions(CRACK_DETECTOR_HANDLE hnd, int crackIndex, int* outPos)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	int num = detector->GetCrackPostions(crackIndex,outPos);
	return num;

}

/************************************************************************/
/*                Set parameters                                        */
/************************************************************************/
CRACK_API int CRACK_DETECTOR_SetSmooth(CRACK_DETECTOR_HANDLE hnd, double sigma)
{//设置高斯滤波的参数
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->gauthSigma = sigma;
	return 0;
}
CRACK_API int CRACK_DETECTOR_SetSeedsRange(CRACK_DETECTOR_HANDLE hnd, double range)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->seedsRange = range;
	return 0;
}

CRACK_API int CRACK_DETECTOR_SetCrackDis(CRACK_DETECTOR_HANDLE hnd, double dis)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->crackDis = dis;
	return 0;
}

CRACK_API int CRACK_DETECTOR_SetCrackLength(CRACK_DETECTOR_HANDLE hnd, double length)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->crackLength = length;
	return 0;
}

CRACK_API int CRACK_DETECTOR_SetPixSize(CRACK_DETECTOR_HANDLE hnd, double size)
{
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->pixSize = size;
	return 0;
}

CRACK_API int CRACK_DETECTOR_SetWidthAverage(CRACK_DETECTOR_HANDLE hnd, double average)
{//
	CCrackDetection* detector = (CCrackDetection*)hnd;
	detector->widthAverage = average;
	return 0;
}
double gauthSigma;//高斯滤波的参数
int seedsRange;//寻找共生边缘时的搜索范围extN
double crackDis;//从最小生成树上断开的两点距离
double crackLength;//保留的裂缝的最小长度阈值
int widthRange;//计算宽度时的搜索范围
int widthAverage;//计算每个种子点处宽度时取平均值的范围