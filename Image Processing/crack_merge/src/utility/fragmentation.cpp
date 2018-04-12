//
// Created by mengyu on 2017/12/8.
//
#include "ClosetPairFromTwoGroup.h"
int fragmentation(int *line, int len, int x, int y) {
    ClosetPairFromTwoGroup closet;
    int xy[2] = {x, y};
    vector<int> pair = closet(line, len, xy, 2);
    if (x == pair[0] && y == pair[1]) {
        xy[0] = pair[2], xy[1] = pair[3];
    } else {
        xy[0] = pair[0], xy[1] = pair[1];
    }
    for (int i = 0; i < len; i += 2) {
        if (line[i] == xy[0] && line[i + 1] == xy[1]) {
            //point i should be deleted
            return i;
        }
    }
    return -1; // error
 }
