#include "tvf.h"
namespace myDesign{
	template<class T>
	class myQueue{
	public:
		myQueue() {
			queue = NULL;
			capacity = head = rear = 0;
		}
		myQueue(int cp) {
			capacity = cp;
			head = rear = 0;
			queue = new T[capacity];
		}
		T front() {
			return queue[head];
		}
		T pop() {
			T headVal = queue[head];
			++head;
			return headVal;
		}
		T push(T val) {
			queue[rear] = val;
			++rear;
			return val;
		}
		bool empty() {
			return rear - head == 0;
		}
		int size() {
			return rear - head;
		}
		~myQueue() {
			delete[] queue;
		}
		void reset() {
			head = rear = 0;
		}
		T operator[](int pos) {
			return queue[pos];
		}

		T *queue;
		int capacity;
		int head, rear;
	};


	void helper(FImage &cutted, int ox, int oy, int thres, myQueue<pair<int, int> > &q) {
		int w, h;
		w = cutted.width();
		h = cutted.height();
		int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
		int dy[] = { 1, 1, 1, 0, -1, -1, -1, 0 };
		q.push(make_pair(ox, oy));
		pair<int, int> top;
		int cnt = 0;
		cnt = 1;
		while (!q.empty()) {
			int sz = q.size();
			int nx, ny;
			for (int i = 0; i < sz; ++i) {
				top = q.front();
				for (int j = 0; j < 8; ++j) {
					nx = top.first + dx[j];
					ny = top.second + dy[j];
					if (cutted[nx * w + ny] == 1) {
						q.push(make_pair(nx, ny));
						++cnt;
						cutted[nx * w + ny] = 2; // visited
					}
				}
				q.pop();
			}
		}
		if (cnt < thres) {
			int sz = q.rear, pos;
			for (int i = 0; i < sz; ++i) {
				top = q[i];
				pos = top.first  * w + top.second;
				cutted[pos] = 0;
			}

		}
		return;

	}



	void cutItViaLength(FImage &ret, FImage &ori, int thres) {
		int w = ori.width();
		int h = ori.height();
		FImage cutted;
		cutted.allocate(w + 2, h + 2);
		cutted.setValue(0);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				cutted[(i + 1) * (w + 2) + j + 1] = ori[i * w + j];
			}
		}
		//cutted.imshow("before cutted");
		int nw, nh;
		nw = w + 2;
		nh = h + 2;
		myQueue<pair<int, int>> q(nw  * nh);

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				if (cutted[(i + 1) * nw + j + 1] == 1) {
					q.reset();
					helper(cutted, i + 1, j + 1, thres, q);
				}
			}
		}
		ret.allocate(w, h);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				ret[i * w + j] = cutted[i * nw + j + 1];
			}
		}
		ret.imshow("cuttedViaLength");
		ret.imwrite("D:\\BridgeProject\\ImgWrite\\temp\\7.cuttedViaLength.jpg");

		return;

	}
}

