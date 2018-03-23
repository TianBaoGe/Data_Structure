//
// Created by tianbao on 17-12-16.
//

#ifndef _MSTEDGE_H
#define _MSTEDGE_H

class MSTEdge {

public:

    int head,tail;
    int weight;
    MSTEdge(int h,int t,int w):head(h),tail(t),weight(w){}
    bool operator<(const MSTEdge& e)const {return weight > e.weight;}
};

#endif //_MSTEDGE_H
