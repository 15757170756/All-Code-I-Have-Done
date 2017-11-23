#include "tvf.h"



void  TensorVoting_new(FImage& voteMag, FImage& voteTh, FImage& seeds, FImage &seedTh) {
	int hei = seeds.height();
	int wid = seeds.width();
	//std::cout << hei << ' ' << wid << std::endl;

	int hei_ext = hei + 2 * WHALF;
	int wid_ext = wid + 2 * WHALF;

	int anchorX = WHALF, anchorY = WHALF;


	double ev[6], tensor[4];
	std::vector<std::vector<std::vector<node>>> cache;
	//std::cout << "calc different angle stick tensor" << std::endl;
	double st, ed;
	st = clock();
	create_cached_vf(cache);
	ed = clock();
//	std::cout << "cost " << (double)(ed - st) / CLOCKS_PER_SEC << std::endl;

	std::vector<std::vector<node> > T(hei_ext, std::vector<node>(wid_ext));
	//form original field
	FImage init(wid, hei);
	double mxd = 0.0, mid;
	float mxf, mif;
	bool dir = 1;
	for (int i = 0; i < hei; i++){
		for (int j = 0; j < wid; j++){
			int idx = i * wid + j;
			int indX = anchorX + j, indY = anchorY + i;
			float mag = seeds[idx];
			if (mag > 0){
				double th = seedTh[idx];
				double nx = -cos(th);// -sin(th);
				double ny = -sin(th);// cos(th);
#ifdef NEWDESIGN
				init[i * wid + j] = seeds[i * wid + j];
				//init[i * wid + j] = 255 - weight.at<uchar>(i, j);
				T[indY][indX].tensor[0] = nx * nx;
				T[indY][indX].tensor[1] = nx * ny;
				T[indY][indX].tensor[2] = nx * ny;
				T[indY][indX].tensor[3] = ny * ny;
#else 
				init[i * wid + j] = 1;
				T[indY][indX].tensor[0] = 1;
				T[indY][indX].tensor[1] = 0;
				T[indY][indX].tensor[2] = 0;
				T[indY][indX].tensor[3] = 1;

#endif
				//if (dir == 0) {
				//	nx = -sin(th);
				//	ny = cos(th);
				//}
				//tensor[0] = nx * nx;
				//tensor[1] = nx * ny;
				//tensor[2] = nx * ny;
				//tensor[3] = ny * ny;
				//convert_tensor_ev(tensor, ev);
				//ev[1] = 0.0;
				//ev[0] *= mag * 255;
				////ev[1] *= mag * 255;
				//convert_ev_tensor(ev, T[indY][indX].tensor);
			
				//init[i * wid + j] = ev[0];// ev[0];
				//mxd = max(mxd, ev[0]);


				
				//T[indY][indX].tensor[0] = 255 - abs(Thres - weight.at<uchar>(i, j));
				//T[indY][indX].tensor[1] = 0;
				//T[indY][indX].tensor[2] = 0;
				//T[indY][indX].tensor[3] = 255 - abs(Thres - weight.at<uchar>(i, j));

				//T[indY][indX].tensor[0] =  255 - weight.at<uchar>(i, j);
				//T[indY][indX].tensor[1] = 0;
				//T[indY][indX].tensor[2] = 0;
				//T[indY][indX].tensor[3] =  255 - weight.at<uchar>(i, j);


			}
		}
	}
	//cout <<"ev[0] max = "<< mxx << endl;
	//for (int i = 0; i < hei; ++i) {
	//	for (int j = 0; j < wid; ++j) {
	//		init[i * wid + j] /= mxd;
	//		//std::cout << init[i * wid + j] << std::endl;
	//	}
	//}
	//for (int i = 0; i < hei; ++i) {
	//	for (int j = 0; j < wid; ++j) {
	//		init[i * wid + j] = seeds[i * wid + j];
	//		//std::cout << init[i * wid + j] << std::endl;
	//	}
	//}


	init.imshow("input seeds");
	seeds.imwrite("D:\\BridgeProject\\ImgWrite\\temp\\4.seeds.jpg");
	//init.imwrite("input_seeds.png");
	//std::cout << init.height() << ' ' << init.width() << ' ' << init.nchannels() << std::endl;



	std::vector<std::vector<node> > stick_normal(hei_ext, std::vector<node>(wid_ext));
	////TODO: cache different angle stick tensor field


	//calc_sparse_field(T, init);


	////calc refined filed
	//calc_vote_stick(stick_normal, T, cache, init, 1);
	calc_vote_ball(stick_normal, init, T, cache, 1);



	FImage stick_before(wid, hei);
	//stick_before.allocate(wid, hei);
#ifndef SUPRESS_BALL
	for (int i = anchorY; i < anchorY + hei; ++i) {
		for (int j = anchorX; j < anchorX + wid; ++j) {
			double val = init[(i - anchorY) * wid + j - anchorX];
			if (fabs(val) > DBL_EPSILON) {
				//T[i][j] += ball[i][j];
				T[i][j].tensor[0] += stick_normal[i][j].tensor[0];
				T[i][j].tensor[1] += stick_normal[i][j].tensor[1];
				T[i][j].tensor[2] += stick_normal[i][j].tensor[2];
				T[i][j].tensor[3] += stick_normal[i][j].tensor[3];

			}
			convert_tensor_ev(T[i][j].tensor, ev);
			//cout << ev[0] << endl;
			//if (ev[0] - ev[1] < 0.1) {
			//	ev[0] = 0;
			//	init[(i - anchorY) * wid + (j - anchorX)] = 0;
			//}
			ev[1] = 0.0;
			convert_ev_tensor(ev, T[i][j].tensor);
			stick_before[(i - anchorY) * wid + (j - anchorX)] = ev[0];
		}
	}
#else
	int cnt;
	double mean_stick;
	cnt = 0;
	FImage ballness(wid, hei);
	mean_stick = 0;
	for (int i = anchorY; i < anchorY + hei; ++i) {
		for (int j = anchorX; j < anchorX + wid; ++j) {
			double val = init[(i - anchorY) * wid + j - anchorX];
			if (fabs(val) > DBL_EPSILON) {
				//T[i][j] += ball[i][j];
				T[i][j].tensor[0] += stick_normal[i][j].tensor[0];
				T[i][j].tensor[1] += stick_normal[i][j].tensor[1];
				T[i][j].tensor[2] += stick_normal[i][j].tensor[2];
				T[i][j].tensor[3] += stick_normal[i][j].tensor[3];
	
			}
			convert_tensor_ev(T[i][j].tensor, T[i][j].ev);
			if (fabs(val) > DBL_EPSILON) {
				mean_stick += T[i][j].ev[0] - T[i][j].ev[1];
				++cnt;
			}
			
		
			//cout << ev[0] << endl;
			//if (ev[0] - ev[1] < 0.1) {
			//	ev[0] = 0;
			//	init[(i - anchorY) * wid + (j - anchorX)] = 0;
			//}
	//		ev[1] = 0.0;
		//	convert_ev_tensor(ev, T[i][j].tensor);
	//		stick_before[(i - anchorY) * wid + (j - anchorX)] = ev[0];
		}
	}
	mean_stick /= (cnt);
	mean_stick *= 2;
	for (int i = anchorY; i < anchorY + hei; ++i) {
		for (int j = anchorX; j < anchorX + wid; ++j) {
			double val = init[(i - anchorY) * wid + j - anchorX];
			stick_before[(i - anchorY) * wid + (j - anchorX)] = T[i][j].ev[0] - T[i][j].ev[1];
			ballness[(i - anchorY) * wid + (j - anchorX)] = T[i][j].ev[1];
		//	if (fabs(val) > DBL_EPSILON && T[i][j].ev[0] - T[i][j].ev[1] < mean_stick) {
			if (fabs(val) > DBL_EPSILON && T[i][j].ev[0] - T[i][j].ev[1] < 0.5 * T[i][j].ev[1]) {
				//less likely to be a stick tensor, may spoil the right direction, set to zero
				T[i][j].ev[0] = T[i][j].ev[1] = 0;
				init[(i - anchorY) * wid + j - anchorX] = 0;
			}
			T[i][j].ev[1] = 0;
			convert_ev_tensor(T[i][j].ev, T[i][j].tensor);
		}
	}
	//ballness.imshow("ballness");

#endif

	//stick_before.imshow("stick before");

//	stick_before.imwrite("stick_before.png");

	std::vector<std::vector<node> > stick(T.size(), std::vector<node>(T[0].size()));

	calc_vote_stick(stick, T, cache, init, 1);
	
	voteMag.allocate(wid, hei);
	voteTh.allocate(wid, hei);

	int rsX, rsY;
	mxd = 0.0f;
	mid = INT_MAX;
	for (int i = anchorY; i < anchorY + hei; ++i) {
		for (int j = anchorX; j < anchorX + wid; ++j) {
			convert_tensor_ev(stick[i][j].tensor, ev);
			mxd = max(mxd, ev[0]);
			mid = min(mid, ev[0]);
			double z = ev[0] - ev[1];
			if (z < 0.1) ev[0] = ev[1] = 0.0;
			convert_ev_tensor(ev, stick[i][j].tensor);
			rsY = i - anchorY;
			rsX = j - anchorX;
			voteMag[rsY * wid + rsX] = ev[0] - ev[1];
			
		//	std::cout << voteMag[rsY * wid + rsX] << std::endl;
			voteTh[rsY * wid + rsX] = atan2(ev[3], ev[2]);
		}
	}

	//std::cout << "max = " << mxd << "min = " << mid << std::endl;
	//for (int i = 0; i < hei; ++i)
	//	for (int j = 0; j < wid; ++j)
	//		voteMag[i * wid + j] = voteMag[i * wid + j] / mx;



	//FILE *MagFile, *ThFile;
	//MagFile = fopen("saliency.raw", "rb");
	//ThFile = fopen("orientation.raw", "rb");
	//fread(voteMag.pData, sizeof(float), w * h, MagFile);
	//fread(voteTh.pData, sizeof(float), w* h, ThFile);
	//for (int i = 0; i < wid * hei; i++){
	//	if (outTh[i] < 0) outTh[i] += PI;
	//	// voteTh[i] -= PI / 2;
	//	if (outTh[i] < 0) outTh[i] += PI;
	//}




	//UCImage voteOut(wid, hei);
	//voteOut.allocate(wid, hei);
	//
	//mxf = 0.0;
	//mif = INT_MAX;
	//for (int i = 0; i < wid * hei; ++i)
	//{
	//	mxf = max(mxf, voteMag[i]);
	//	mif = min(mif, voteMag[i]);
	//}
	//for (int i = 0; i < wid * hei; ++i) {
	//	voteOut[i] = (uchar)((voteMag[i] - mif) / (mxf - mif) * 255);
	//}
	//cout << mxf << ' ' << mif << endl;
	//voteOut.imwrite("voteout.png");

	//UCImage outer, outer_1;

	//outer.imread("ans.png");
	//outer.desaturate(outer_1);
	//outer.imshow("outer");
	//std::cout << outer.height() << ' ' << outer.width() << ' ' << outer.nchannels() << std::endl;
	//for (int i = 0; i < w * h; ++i) {
	//	voteMag[i] = outer_1[i] ;
	//}

	//////////////////////////////////////////////////////////
	//FILE *sali = fopen("saliency.raw", "rb");
	//FILE *orien = fopen("orientation.raw", "rb");
	//fread(voteMag.pData, sizeof(float), w * h, sali);
	//fread(voteTh.pData, sizeof(float), w * h, orien);
	//fclose(sali);
	//fclose(orien);


	//////////////////////////////////////////////////////////
	//voteMag.imshow("vote mag");
	//voteMag.imwrite("voteMag.png");
	//voteTh.imagesc("vote th");

	ed = clock();
	//std::cout << "TENSORVOTING cost " << (double)(ed - st) / CLOCKS_PER_SEC << " s" << std::endl;




	//GetLocalPeak_new(voteMag, voteTh, votePeak, 1);
	//GetLocalPeak(voteMag, voteTh, votePeak);

	//freopen("point.txt", "w", stdout);
	

	//GetLocalPeak(voteMag, votePeak);


	//for (int i = 0; i < hei; ++i) {
	//	for (int j = 0; j < wid; ++j){
	//		if (votePeak[i * wid + j] > 0.3) {
	//			cout << i << ' ' << j << ' ' << voteTh[i * wid + j] * 180 / PI <<' '<<voteMag[i * wid + j]<< endl;
	//		}
	//	}
	//}
	//
	/*FImage finalCrack;
	int crackNum = CrackThresholding(voteMag, votePeak, finalCrack, 0.3, 0.5);
	printf("%d\n", crackNum);*/


	//finalCrack.imwrite("final.png");
	//ShowCracks(finalCrack);

#ifdef DEBUG
	{
		std::vector<std::vector<node>> stf(WS, std::vector<node>(WS));

		create_stick_tensorfield(stf, PI);
		FImage stf_mag(WS, WS);
		stf_mag.allocate(WS, WS);

		double ev[6];
		for (int i = 0; i < WS; ++i) {
			for (int j = 0; j < WS; ++j) {
				convert_tensor_ev(stf[i][j].tensor, ev);
				/*		std::cout << pbf[i][j].tensor[0] << ' ';
				std::cout << pbf[i][j].tensor[1] << ' ';
				std::cout << pbf[i][j].tensor[2] << ' ';
				std::cout << pbf[i][j].tensor[3] << ' ';*/
				stf_mag[i* WS + j] = ev[0] - ev[1];
				printf("%.7f ", stf_mag[i * WS + j]);
			}
			printf("\n");
			//std::cout << std::endl;
		}
		stf_mag.imagesc("stick_mag");
		stf_mag.imwrite("stick_mag.png");
	}
#endif
	return;
}