//
// Created by tianbao on 17-12-15.
//

#ifndef _VERTEX_H
#define _VERTEX_H

#include "Edge.h"

template <typename V,typename E>
class Vertex {

public:

    V data;
    int inDegree;
    int outDegree;
    Edge<E>*next;

    Vertex(const V& v = (V)0 ,Edge<E>* n = nullptr,int in = 0,int out = 0):data(v),next(n),inDegree(in),outDegree(out){}
    ~Vertex() {if(next) delete next;}

    bool operator== (const Vertex& temp) const {return data == temp.data;}
    bool operator< (const Vertex& temp) const {return data < temp.data;}
};
#endif //_VERTEX_H
