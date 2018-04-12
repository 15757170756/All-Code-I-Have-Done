
#include "longestPathByPoint.h"
#include <iostream>
#include <fstream>

cv::KeyPoint Edges::getPointViaId(int id) const
{
	if (id >= xy_arr.size()) return cv::KeyPoint();
	return xy_arr[id];
}

const vector<Edge>& Edges::getEdges() const 
{
	return edges;
}
const vector<int>& Edges::getHead() const
{
	return head;
}

void Edges::add_edge(int u, int v, float w)
{
	edges.emplace_back(v, head[u], w);
	assert(u < head.size());
	head[u] = edges.size() - 1;
	edges.emplace_back(u, head[v], w);
	assert(v < head.size());
	head[v] = edges.size() - 1;
}
//deprecated
//pair<int,int> Edges::get_xy(int id) const
//{
//	assert(id < xy_arr.size() && id >= 0);
//	int x = static_cast<int>(xy_arr[id].pt.x);
//	int y = static_cast<int>(xy_arr[id].pt.y);
//	return make_pair(x, y);
//}
/// \brief insert point & return id
int Edges::insert_point(const cv::KeyPoint &point)
{
	
	int x = point.pt.x;
	int y = point.pt.y;
	pair<int, int> xy(x, y);
	// id from 0 to head.size() - 1
	int u = get_id(x, y);
	if (u == -1) {
		u = head.size();
		id[xy] = u;
		head.push_back(-1);
		xy_arr.push_back(point);
	} 
	return u;
}
int Edges::get_id(int x, int y)
{
	pair<int, int> xy(x, y);
	int u;
	
	if (id.find(xy) != id.end())
	{
		u = id[xy];
//		std::cout << "itersect at ("<<x<<","<<y<<")" << std::endl;
	}
	else
	{
		u = -1;
	}
//	std::cout << "(" << x << ", " << y << ")" << "->"<<u<<std::endl;
	return u;
}

//deprecated interface
//void Edges::addLine(const int* const line_xy, int len)
//{
	//assert(len > 2);

//	if (len <= 2) return;
//	int pre_x = line_xy[0];
//	int pre_y = line_xy[1];
//	int u;
//	u = get_id(pre_x, pre_y);
//	auto calcdis = [](int xa, int ya, int xb, int yb)
//	{
//		return sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
//	};
//	for (int i = 2; i < len; i += 2)
//	{
//		int x = line_xy[i];
//		int y = line_xy[i + 1];
//		int v = get_id(x, y);
//		add_edge(u, v, calcdis(pre_x, pre_y, x, y));
//		pre_x = x;
//		pre_y = y;
//		u = v;
//	}
//}
//
//void Edges::addLine(const vector<int> xy_arr)
//{
//	addLine(xy_arr.data(), xy_arr.size());
//}
void Edges::addLine(const vector<cv::KeyPoint> xy_arr)
{
	int len = xy_arr.size();
//	if (len <= 1) return;
	int u = insert_point(xy_arr[0]);
	auto calcdis = [](const cv::Point2f &p1, const cv::Point2f &p2)
	{
		return cv::norm(p1 - p2);
	};
	for (int i = 1; i < len; ++i)
	{
		int v = insert_point(xy_arr[i]);
		add_edge(u, v, calcdis(xy_arr[i - 1].pt, xy_arr[i].pt));
		u = v;
	}
}


static int getFirstValid(const vector<bool>& valid, int start)
{
	int sz = valid.size();
	int select = -1;
	for (int i = start; i < sz; ++i)
	{
		if (valid[i])
		{
			select = i;
			break;
		}
	}
	return select;
}
void SplitTree::operator()(const Edges *const edge_struct, int min_points_thres)
{
	edge_struct_ = edge_struct;
	int n = edge_struct_->getHead().size();
//	std::cout << "there are " << n  << " points" << std::endl;
	init(n);
	int start = 0;
	for (; ;)
	{
		start = getFirstValid(valid_, start);
		if (start < 0) {
			std::cout << "no Point valid" << std::endl;
			break;
		}
//		std::cout << "start from " << start << std::endl;
//		std::cout << "bfs start" << std::endl;
		int ed = bfs(bfs(start));
//		std::cout << "bfs complte" << std::endl;
		vector<int> path;
		int status = getPath(path, ed);
//		std::cout << "get path complete" << std::endl;
		if (path.size() > min_points_thres) {
			line_dis_.push_back(dis_[ed]);
			lines_.push_back(path);
//			std::cout << "line_size = "<<lines_[lines_.size() - 1].size() << std::endl;
		}
	}
}
vector<float> SplitTree::getLineDis() const
{
	return line_dis_;
}

void SplitTree::init(int nPoint)
{
	valid_.resize(nPoint, true);
	lines_.clear();
	line_dis_.clear();
}

int SplitTree::getLines(vector<vector<cv::KeyPoint> > &lines_out) const
{
	int sz = lines_.size();
	for (int i = 0; i < sz; ++i)
	{
		vector<cv::KeyPoint> new_line;
		for (int j = 0; j < lines_[i].size(); ++j) {
			cv::KeyPoint xy = edge_struct_->getPointViaId(lines_[i][j]);
			new_line.push_back(xy);
		}
		lines_out.push_back(new_line);
	}
	return 0;
}
int SplitTree::getSortedLines(vector<vector<cv::KeyPoint> > &lines_out, std::function<bool(const vector<cv::KeyPoint> &v1, const vector<cv::KeyPoint> &v2)> func)
{
	getLines(lines_out);
	sort(lines_out.begin(), lines_out.end(), func);
	return 0;
}
int SplitTree::bfs(int s)
{
	const vector<Edge> &edges = edge_struct_->getEdges();
	const vector<int> &head = edge_struct_->getHead();
	int n = head.size();
	vector<bool> visited(n, false);
	vector<int> depth(n, 0);
	dis_.resize(n, .0f);
	pre_.resize(n, -1);
	for (int i = 0; i < n; ++i)
	{
		pre_[i] = -1;
	}
	std::queue<int> q;
	q.push(s);
	int cnt = 0;
	visited[s] = true;
#if 0
	std::cout << "bfs start" << std::endl;
	std::ofstream pf("points.txt");
	pf << "bfs start" << std::endl;
#endif
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
//		pf << u << std::endl;
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].to;
//			pf << v << std::endl;
			if (!valid_[v]) continue;
			float w = edges[i].w;
			if (!visited[v])
			{
				visited[v] = true;
				depth[v] = depth[u] + 1;
				pre_[v] = u;
				dis_[v] = dis_[u] + w;
				q.push(v);
			}
		}
//		std::cout << std::endl;
	}
//	std::cout << "bfs end" << std::endl;
	int mx_depth = -1;
	int remote_id = -1;
	for (int i = 0; i < n; ++i)
	{
		if (valid_[i] && depth[i] > mx_depth)
		{
			mx_depth = depth[i];
			remote_id = i;
		}
	}
//	std::cout << depth[remote_id] << ' ' << remote_id << std::endl;
	return remote_id;
}
int SplitTree::getPath(vector<int> &onePath, int s)
{
	//vector<int> onePath;
//	std::ofstream of("revers.txt");
	onePath.clear();
	while (s != -1)
	{
		onePath.push_back(s);
		valid_[s] = false;
//		of << s << std::endl;
		s = pre_[s];
		
	}
	std::reverse(onePath.begin(), onePath.end());
	return 0;
}
