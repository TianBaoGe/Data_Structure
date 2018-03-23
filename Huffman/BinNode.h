//
// Created by tianbao on 17-11-11.
//

#ifndef _BINNODE_H
#define _BINNODE_H

#include <cstdlib>
#include <queue>
using std::rand;
using std::queue;


#define HasLChild(x) ((x).Lc)
#define HasRChild(x) ((x).Rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define IsLeaf(x) (!HasChild(x))


template <typename T>
class BinNode
{
public:

    BinNode():parent(nullptr),Lc(nullptr),Rc(nullptr) {}
    BinNode(T _data,BinNode<T>*p,BinNode<T>*l = nullptr,BinNode<T>*r = nullptr):
            data(_data),parent(p), Lc(l),Rc(r){}

    T data;
    BinNode<T>* parent;
    BinNode<T>* Lc;
    BinNode<T>* Rc;


};

#endif
