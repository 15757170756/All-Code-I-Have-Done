//
// Created by mengyu on 2017/12/7.
//

#ifndef CLOSETPAIRFROMTWOGROUP_CLOSETPAIRFROMTWOGROUP_H
#define CLOSETPAIRFROMTWOGROUP_CLOSETPAIRFROMTWOGROUP_H
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

using std::pair;
using std::set;
using std::map;
using std::vector;
using std::make_pair;

class ClosetPairFromTwoGroup {
public:
    struct node {
        int x;
        int y;
        int group;
        node():x(-1),y(-1),group(-1){}
        node(int x_, int y_, int g_):x(x_), y(y_), group(g_){}
        bool operator<(const node &other) {return x < other.x;}
    };
	vector<int> findClosetPairNaive(const int * const lineA, int lenA, 
        const int * const lineB, int lenB);

    vector<int> operator()(const int * const lineA, int lenA, 
    const int * const lineB, int lenB); //return xyxy
private:
    void init();
    vector<node> points;
    vector<int> idx;
    vector<int> closetPair;
    node pA, pB;
    double min_dist;
    double findCloset(int low, int high);

    double dist(const node &p1, const node &p2);

    bool cmpy(int &idx1, int &idx2);
};

#endif //CLOSETPAIRFROMTWOGROUP_CLOSETPAIRFROMTWOGROUP_H
