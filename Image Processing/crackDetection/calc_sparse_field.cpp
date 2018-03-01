#include "tvf.h"
void calc_sparse_field(std::vector<std::vector<node> > &T, FImage& seeds) {
	//calc max 
	float mx = 0.0;
	int px = seeds.nelements();
	int hei = T.size() - WHALF * 2;
	int wid = T[0].size() - WHALF * 2;

	
	int indX, indY;
	for (int i = 0; i < hei; ++i) {
		for (int j = 0; j < wid; ++j) {
			indY = i + WHALF;
			indX = j + WHALF;
			if (seeds[i * wid + j] > 0)
			{
				T[indY][indX].tensor[0] = 1.0;
				T[indY][indX].tensor[1] = 0.0;
				T[indY][indX].tensor[2] = 0.0;
				T[indY][indX].tensor[3] = 1.0;
				
			}
			else{
				T[indY][indX].tensor[0] = 0.0;
				T[indY][indX].tensor[1] = 0.0;
				T[indY][indX].tensor[2] = 0.0;
				T[indY][indX].tensor[3] = 0.0;
			}
		}
	}
	return;
}