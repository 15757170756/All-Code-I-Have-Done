#include <vector>
#include <map>
#include <cassert>
#include <queue>
#include <iostream>
#include <functional>

//use opencv keypoint to represent point with width
#include <opencv2/opencv.hpp>
class SplitTree;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;
struct Edge
{
	int to;
	int next;
	float w;
	Edge(int to_, int next_, float w_) :to(to_), next(next_),  w(w_){}
};
class Edges
{
//	friend SplitTree;
public:
//	void addLine(const int * const line_xy, int len); //line_xy = [xyxyxyxy...] len = line_xy.size()
//	void addLine(const vector<int> xy_arr);
	void addLine(const vector<cv::KeyPoint> xy_arr);
//	pair<int, int> get_xy(int id) const;
	int insert_point(const cv::KeyPoint &point);
	const vector<Edge> &getEdges() const;
	const vector<int> &getHead() const;
	cv::KeyPoint getPointViaId(int id) const;
	int get_id(int x, int y);

private:
	vector<Edge> edges;
	void add_edge(int u, int v, float w);
	
	
	vector<int> head;
	//give every point(x,y) an id to compress memory usage
	map<pair<int, int>, int> id;
//	vector<pair<int, int> > xy_arr;
	vector<cv::KeyPoint> xy_arr;
	int cnt;
};
class SplitTree
{
public:
	void operator()(const Edges * const edge_struct, int min_points_thres = 20);
	int getLines(vector<vector<cv::KeyPoint> > &lines_out) const;
	int getSortedLines(vector<vector<cv::KeyPoint> > &lines_out, std::function<bool(const vector<cv::KeyPoint> &v1, const vector<cv::KeyPoint> &v2)> func);
	vector<float> getLineDis() const;
private:
	void init(int n);
	const Edges* edge_struct_;
	int bfs(int s);
	int getPath(vector<int> &path, int s);
	vector<vector<int> > lines_;
	vector<float> line_dis_;
	vector<float> dis_;
	vector<int> pre_;
	vector<bool> valid_;

};



