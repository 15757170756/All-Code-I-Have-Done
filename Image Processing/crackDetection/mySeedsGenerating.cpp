#include "tvf.h"
#include <stack>

//////////////////////////////////////////////////////////////////////////
//needs to fix
//////////////////////////////////////////////////////////////////////////
namespace myDesign {
	int trap(unsigned char *height, float *seeds, int w) {
		int n = w;

		// if (n < 3) return 0;
		stack<int> st;
		//for (int i = 0; i < n; ++i) height[i] = (int)height[i] / 4 * 4;
		int i = 0;
		while (i < n && height[i] == 0) ++i;
		int ans = 0;
		for (int j = i; j < n; ++j) {
			if (st.empty() || height[j] <= height[st.top()]) {
				st.push(j);
			//	cout << j << endl;
			}
			else {
				// cout<<height[st.top()]<<' ';
				int pre = j;//= st.top();

				while (!st.empty() && height[j] > height[st.top()]) {
					//ans += (height[j] - height[st.top()]) * (j - pre);

					pre = st.top();
					st.pop();
					//int w = st.empty() ? 0 : pre - st.top();
					//cout<<(height[j] - height[pre]) * w<<endl;
					//ans += (height[j] - height[pre]) * w;
				}
				seeds[(j + pre) / 2]++;
				//int minus = (j - pre - 1) * (height[j] - height[pre]);
				//if (st.empty()) ans -= minus;
				// cout<<"minus "<< minus<<endl;
				// cout<<ans<<endl;
				st.push(j);
			}
		}
	//	cout << st.size() << endl;
		return ans;

	}
	void myGetSeeds(cv::Mat gray, FImage &seeds) {
		int w, h;
		w = gray.cols;
		h = gray.rows;



		if (seeds.IsEmpty()) {
			seeds.allocate(w, h);
		}
		seeds.setValue(0);
		for (int i = 0; i < h; ++i) {
			trap(gray.data + i * w, seeds.pData + i * w, w);
		}
		return;
	}

}