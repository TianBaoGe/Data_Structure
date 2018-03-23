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

    Edge(const E& e,int w):data(e),wegiht(w){}

    bool operator<(const Edge& e) const {return wegiht<e.wegiht;}
};
#endif //_EDGE_H
