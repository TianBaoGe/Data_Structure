//
// Created by tianbao on 17-12-15.
//

#ifndef _VERTEX_H
#define _VERTEX_H

template <typename V>
class Vertex {

public:

    V data;
    int inDegree;
    int outDegree;

    Vertex(const V& v = (V)0,int in = 0,int out = 0):data(v),inDegree(in),outDegree(out){}

    bool operator== (const Vertex& temp) const {return data == temp.data;}
    bool operator< (const Vertex& temp) const {return data < temp.data;}
};
#endif //_VERTEX_H
