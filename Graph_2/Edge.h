//
// Created by tianbao on 17-12-15.
//

#ifndef _EDGE_H
#define _EDGE_H

template <typename E>
class Edge {

public:

    E data;
    int wegiht;
    Edge<E>* next;
    int tail;

    Edge(const E& e,int t,int w,Edge<E>*n = nullptr):data(e),tail(t),wegiht(w),next(n){}

    bool operator<(const Edge& e) const {return wegiht<e.wegiht;}
};
#endif //_EDGE_H
