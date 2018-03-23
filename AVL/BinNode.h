//
// Created by tianbao on 17-11-11.
//

#ifndef _BINNODE_H
#define _BINNODE_H

#include <cstdlib>
#include <queue>
using std::rand;
using std::queue;

//p为树节点指针，x为树节点
#define stature(p) ((p)?(p)->height:-1) //节点高度，约定好空树高度为-1
#define IsRoot(x) (!((x).parent)) //当前节点是否为根节点
#define IsLChild(x) (!IsRoot(x) && &(x) == ((x).parent->Lc))
#define IsRChild(x) (!IsRoot(x) && &(x)== ((x).parent->Rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).Lc)
#define HasRChild(x) ((x).Rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define BalFac(x) ( stature((x).Lc) - stature((x).Rc)) //x要用（）包起来，因为你是*g传进来，实际转换的时候可能会分开
#define AvlBalance(x) ((-2 < BalFac(x)) && ( BalFac(x) < 2 ))
#define tallerChild(x) (stature((x)->Lc) > stature((x)->Rc)?(x)->Lc:(stature((x)->Lc)<stature((x)->Rc)?(x)->Rc:(IsLChild(*(x))?(x)->Lc:(x)->Rc)))

template <typename T>
class BinNode
{
public:

    BinNode():parent(nullptr),Lc(nullptr),Rc(nullptr),height(0) {}
    BinNode(T _data,BinNode<T>*p,BinNode<T>*l = nullptr,BinNode<T>*r = nullptr,int h = 0):
            data(_data),parent(p), Lc(l),Rc(r),height(h){}
    int size();//统计当前节点后代总数，即以该节点为根的子树规模
    int size(BinNode<T>*);
    BinNode<T>* insertAsLc(const T&);
    BinNode<T>* insertAsRc(const T&);
    BinNode<T>* succ();//获得当前节点在中序遍历中的直接后继
    bool operator< (const BinNode& temp ) { return this->data < temp.data;}
    bool operator== (const BinNode& temp) { return this->data == temp.data;}


    T data;
    BinNode<T>* parent;
    BinNode<T>* Lc;
    BinNode<T>* Rc;
    int height;


};

template <typename T>
int BinNode<T>::size() {

}

//有待测试证明正确性
template <typename T>
int BinNode<T>::size(BinNode<T>*root) {

    if(!root) return 0;
    return 1+size(root->Rc)+size(root->Lc);
}


template <typename T>
BinNode<T>* BinNode<T>::insertAsLc(const T& temp) {
    return Lc = new BinNode(temp,this);//temp为数据，当前节点为父母，左右孩子都为空
}


template <typename T>
BinNode<T>* BinNode<T>::insertAsRc(const T& temp) {
    return Rc = new BinNode(temp,this);//temp为数据，当前节点为父母，左右孩子都为空
}


template <typename T>
BinNode<T>* BinNode<T>::succ() {

    BinNode<T>*temp = this;
    if(Rc) {
        temp = Rc;
        while(HasRChild(*temp)) temp = temp->Rc;
    }
    else {
        while(IsRChild(*temp)) temp = temp->parent;
        temp = temp->parent;
    }
    return temp;
}
#endif
