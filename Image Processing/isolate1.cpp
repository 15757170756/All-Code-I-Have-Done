#include "tvf.h"
namespace myDesign{
	bool noCross(FImage &cutted, int x, int y, int w, int l){
		double cnt = 0;
		for (int i = 0; i < l; ++i) {
			cnt += cutted[x * w + y + i];
		}
		if (cnt > 0) return false;
		for (int i = 0; i < l; ++i) {
			cnt += cutted[(x + i) * w + y];
		}
		if (cnt > 0) return false;
		for (int i = 0; i < l; ++i) {
			cnt += cutted[(x + i) * w + y + l];
		}
		if (cnt > 0) return false;
		for (int i = 0; i < l; ++i) {
			cnt += cutted[(x + l) * w + y + i];
		}
		if (cnt > 0) return false;
		return true;
	}
	void setZero(FImage &cutted, int x, int y, int w, int l){
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < l; ++j){
				cutted[(x + i) * w + y + j] = 0;
			}
		}
		return;
	}
	void cutItAround(FImage &ret, FImage &ori, int r) {
		int w = ori.width();
		int h = ori.height();
		int l = 2 * r + 1;
		FImage cutted;
		cutted.allocate(w + l, h + l);
		cutted.setValue(0);
		int nh, nw;
		nh = h + l;
		nw = w + l;
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cutted[i * nw + j] = ori[i * w + j];
			}
		}
		//cutted.imshow("cutted Around before");
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j){
				if (noCross(cutted, i, j, nw, l)){
					setZero(cutted, i, j, nw, l);
				}
			}
		}
		ret.allocate(w, h);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j)
				ret[i * w + j] = cutted[i * nw + j];
		}


		//ret.imshow("cuttedAround");
		return;
	}
}