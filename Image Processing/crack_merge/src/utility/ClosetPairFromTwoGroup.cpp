//
// Created by mengyu on 2017/12/7.
// find close point pair from two group
// inspire by find close point pair from one group
// http://blog.csdn.net/hackbuteer1/article/details/7482232
//

#include <cfloat>
#include "ClosetPairFromTwoGroup.h"
double ClosetPairFromTwoGroup::dist(const node &p1, const node &p2) {
    //calc distance
    if (p1.group == p2.group) return DBL_MAX;
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dist = sqrt(dx * dx + dy * dy);
    //update closet pair
    if (dist < min_dist) {
        pA = p1;
        pB = p2;
        min_dist = dist;
    }
    return dist;
}
void ClosetPairFromTwoGroup::init() {
    min_dist = DBL_MAX;
    points.clear();
    closetPair.clear();
}
vector<int> ClosetPairFromTwoGroup::operator()(const int * const lineA, int lenA, const int * const lineB, int lenB) {
    init();
    for (int i = 0; i < lenA; i += 2) {
        points.emplace_back(lineA[i], lineA[i + 1], 1);
    }
    for (int i = 0; i < lenB; i += 2) {
        points.emplace_back(lineB[i], lineB[i + 1], 2);
    }
    sort(points.begin(), points.end());
    idx.resize(points.size());
    findCloset(0, points.size());
    closetPair.push_back(pA.x);
    closetPair.push_back(pA.y);
    closetPair.push_back(pB.x);
    closetPair.push_back(pB.y);
    return closetPair;
}
bool ClosetPairFromTwoGroup::cmpy(int &idx1, int &idx2) {
    return points[idx1].y < points[idx2].y;
}
double ClosetPairFromTwoGroup::findCloset(int low, int high) {
    using std::min;
    if (high - low < 2) return DBL_MAX;
    if (low + 2 == high) {
        return dist(points[low], points[low + 1]);
    }
    if (low + 3 == high) {
        return min(dist(points[low], points[low + 1]), min(dist(points[low + 1], points[low + 2]), dist(points[low], points[low + 2])));
    }
    int mid = low + (high - low) / 2;
    double ans = min(findCloset(low, mid), findCloset(mid, high));
    int within = 0;
    for (int i = low; i < high; ++i) {
        if (abs(points[i].x - points[mid].x) <= ans) {
            idx[within++] = i;
        }
    }
    sort(idx.begin(), idx.begin() + within, [this](int a, int b)->bool{ return this->points[a].y < this->points[b].y; });
    for (int i = 0; i < within; ++i) {
        for (int j = i + 1; j < within; ++j) {
            if (points[idx[j]].y - points[idx[i]].y >= ans) {
                break;
            }
            ans = min(ans, dist(points[idx[i]], points[idx[j]]));
        }
    }
    return ans;
}
vector<int> ClosetPairFromTwoGroup::findClosetPairNaive(const int * const lineA, int lenA, const int * const lineB, int lenB)

{
    vector<int> xAyAxByB;
    double min_dis = DBL_MAX;
    auto euclideanDis = [](int xa, int xb, int ya, int yb)
    {
        return sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
    };
    int ca = 0, cb = 0;
    for (int i = 0; i < lenA; i += 2)
    {
        int xa = lineA[i];
        int ya = lineA[i + 1];
        for (int j = 0; j < lenB; j += 2)
        {
            int xb = lineB[j];
            int yb = lineB[j + 1];
            double dis = euclideanDis(xa, xb, ya, yb);
            if (dis < min_dis)
            {
                min_dis = dis;
                ca = i;
                cb = j;
//                std::cout<<"mindis = "<<min_dis<<' '<<xa<<' '<<ya<<' '<<xb<<' '<<yb<<std::endl;

            }
        }
    }
    xAyAxByB.push_back(lineA[ca]);
    xAyAxByB.push_back(lineA[ca + 1]);
    xAyAxByB.push_back(lineB[cb]);
    xAyAxByB.push_back(lineB[cb + 1]);
//    std::cout<<min_dis<<std::endl;
//    std::cout<<lineA[ca]<<' '<<lineA[ca + 1]<<' '<<lineB[cb]<<' '<<lineB[cb + 1]<<std::endl;
    return xAyAxByB;
}