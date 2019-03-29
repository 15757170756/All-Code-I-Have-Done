double gray_std(Mat img)
{
	int totalPixNum = img.rows*img.cols;
	//int cnt[256];
	//double Pg[256];
	//memset(cnt, 0, sizeof(cnt));
	//memset(Pg, 0, sizeof(Pg));
	vector<int> cnt(256, 0);
	vector<double> Pg(256, 0.0);
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			int pix = img.at<uchar>(i, j);
			++cnt[pix];
		}
	}
	for (int i = 0; i < 256; ++i) {
		Pg[i] = cnt[i]*1.0 / totalPixNum;
	}
	double aveg = 0;
	for (int i = 0; i < 256; ++i)
		aveg += i*Pg[i];
	double graystd = 0;

	for (int i = 0; i < 256; ++i) {
		graystd += (i - aveg)*(i - aveg)*Pg[i];
	}

	graystd = sqrt(graystd);
	return graystd;
}
