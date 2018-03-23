//
// Created by tianbao on 17-12-6.
//

#ifndef _AVL_H
#define _AVL_H


#include "BinNode.h"
#include <algorithm>
#include <stack>
#include <iostream>
using std::max;
using std::stack;
using std::swap;

template <typename T>
class AVL
{
public:

    AVL():_size(0),_root(nullptr){}
    AVL(BinNode<T>* root,int size):_root(root),_size(size){}
    ~AVL() {}
    int size() const { return _size;}
    BinNode<T>* root() const {return _root;}//不知道表现的行为是否符合预期
    bool empty() const { return !_root;}
    BinNode<T>* insertAsRoot (const T& e);
    BinNode<T>* insertAsLc (BinNode<T>*x, const T& e);//e作为x的左孩子插入
    BinNode<T>* insertAsRc (BinNode<T>*x, const T& e);//e作为x的右孩子插入
    BinNode<T>* attachAsLTree (BinNode<T>* x ,AVL<T>*& t);//T作为x的左子树插入
    BinNode<T>* attachAsRTree (BinNode<T>* x ,AVL<T>*& t);//T作为x的右子树插入
    AVL<T>* secede(BinNode<T>* x);//将子树x从当前树中摘除，转变为一颗独立的树
    bool operator== (const AVL<T>&tree) const {return equals(_root,tree._root);}
    bool operator< (const AVL<T>&tree) const { return _root&& tree._root && (_root < tree._root);}
    BinNode<T>* & search(const T& e) { return searchIn(_root,e,_hot = nullptr);}
    BinNode<T>* insert(const T& e);
    bool remove(const T& e);

    void show() {show(_root);}
    void show(BinNode<T>* root) {

        if(!root) return;
        show(root->Lc);
        std::cout << root->data << std::endl;
        show(root->Rc);
    }

protected:

    int _size;
    BinNode<T>* _root;
    virtual int updateHeight(BinNode<T>* temp);//更新当前节点的高度,因为AVL树和红黑树的更新方式不一样，所以该函数为虚拟函数
    void updateHeightAbove(BinNode<T>*root);//更新当前节点路径上全部祖先的高度
    bool equals( BinNode<T>* first,BinNode<T>* second) const;

    BinNode<T>* _hot;
    BinNode<T>* connect34(BinNode<T>*,BinNode<T>*,BinNode<T>*,BinNode<T>*,BinNode<T>*,BinNode<T>*,BinNode<T>*);
    BinNode<T>* rotateAt(BinNode<T>*);
    BinNode<T>* & searchIn(BinNode<T>*& v,const T& e,BinNode<T>*& hot);
    BinNode<T>* removeAt(BinNode<T>* & x,BinNode<T>* & hot);
    BinNode<T>*& FromParentTo(BinNode<T>*&x) {

        if(IsRoot(*x)) return _root;
        if(IsLChild(*x)) return x->parent->Lc;
        else return x->parent->Rc;
    }
};

template <typename T>
int AVL<T>::updateHeight(BinNode<T> *temp) {

    return temp->height = max(stature(temp->Lc),stature(temp->Rc)) + 1;
}

template <typename T>
void AVL<T>::updateHeightAbove(BinNode<T> *root) {

    while(root) { updateHeight(root); root = root->parent; }
}

template <typename T>
BinNode<T>* AVL<T>::insertAsRoot (const T& e){

    _size = 1;
    _root = new BinNode<T>;
    _root->data = e;
    return _root;
}

template <typename T>
BinNode<T>* AVL<T>::insertAsLc (BinNode<T>*x, const T& e) {
    ++_size;
    x->insertAsLc(e);
    updateHeightAbove(x);
    return x->Lc;
}

template <typename T>
BinNode<T>* AVL<T>::insertAsRc (BinNode<T>*x, const T& e) {
    ++_size;
    x->insertAsRc(e);
    updateHeightAbove(x);
    return x->Rc;
}

template <typename T> //因为要将T树置空，所以必须传入该树根节点的引用
BinNode<T>* AVL<T>::attachAsLTree (BinNode<T>* x ,AVL<T>* &t) {

    if(x->Lc = t->_root) x->Lc->parent = x;//子树的父母置为x,彻底连接子树
    _size += t->_size;
    updateHeightAbove(x);
    //连接好子树后，更新T树
    t->_root = nullptr;
    t->_size = 0;
    return x;
}

template <typename T> //因为要将T树置空，所以必须传入该树根节点的引用
BinNode<T>* AVL<T>::attachAsRTree (BinNode<T>* x ,AVL<T>* &t) {

    if(x->Rc = t->_root) x->Rc->parent = x;//子树的父母置为x,彻底连接子树
    _size += t->_size;
    updateHeightAbove(x);
    //连接好子树后，更新T树
    t->_root = nullptr;
    t->_size = 0;
    delete t;//彻底删除该树
    return x;
}


template <typename T>//判断两个树是否相等
bool AVL<T>::equals( BinNode<T>* first,BinNode<T>* second) const {

    if (!first && !second) return true;//两个空节点，相等
    if(!first || !second) return false;//其中一个为空节点，不相等
    if (first->data == second->data) return equals(first->Lc,second->Lc) && equals(first->Rc,second->Rc);
    return false;
}


template <typename T>
AVL<T>* AVL<T>::secede(BinNode<T>* x) {

    FromParentTo(*x) = nullptr;//x的父母指向为空了，但x的父母仍然不变
    updateHeightAbove(x->parent);
    AVL<T>* newTree = new AVL<T>;
    newTree->_root = x;
    x->parent = nullptr;//彻底切断联系
    newTree->_size = x->size();
    _size -= newTree->_size;
    return newTree;
}


template <typename T>
BinNode<T>* & AVL<T>::searchIn(BinNode<T>*& v,const T& e,BinNode<T>*& hot) {

    if(!v || v->data == e) return v;
    hot = v;
    return searchIn((v->data > e)?v->Lc:v->Rc,e,hot);
}


template <typename T>
bool AVL<T>::remove(const T &e) {

    BinNode<T>* &x = search(e);
    if(!x) return false;
    removeAt(x,_hot);_size--;

    for(BinNode<T>* g = _hot;g;g = g->parent) {

        if(!AvlBalance(*g)) {

            BinNode<T>* temp = g->parent;
            int judge;
            if(IsLChild(*g)) judge = 0;
            else judge = 1;
            FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
            if(!temp) g = _root;
            else if(judge == 0) g = temp->Lc;
            else g = temp->Rc;
        }
        updateHeight(g);
    }
    return true;
}

template <typename T>
BinNode<T>* AVL<T>::removeAt(BinNode<T>* & x,BinNode<T>* & hot) {

    BinNode<T>* w = x;
    BinNode<T>* succ = nullptr;
    if(!HasLChild(*x)) succ = x = x->Rc;
    else if(!HasRChild(*x)) succ = x = x->Lc;
    else {

        w = w->succ();
        swap(w->data,x->data);
        BinNode<T>* u = w->parent;
        ((u == x)?u->Rc:u->Lc) = succ = w->Rc;
    }

    hot = w->parent;
    if(succ) succ->parent = hot;
    delete w;
    return succ;
}


template <typename T>
BinNode<T>* AVL<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c, BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2,
                              BinNode<T>* T3) {

    a->Lc = T0;if(T0) T0->parent = a;
    a->Rc = T1;if(T1) T1->parent = a;updateHeight(a);
    c->Lc = T2;if(T2) T2->parent = c;
    c->Rc = T3;if(T3) T3->parent = c;updateHeight(c);
    b->Lc = a; a->parent = b;
    b->Rc = c; c->parent = b; updateHeight(b);
    return b;
}


template <typename T>
BinNode<T>* AVL<T>::rotateAt(BinNode<T>* v) {

    BinNode<T>*p = v->parent;BinNode<T>*g = p->parent;
    if(IsLChild(*p)){
        if(IsLChild(*v)) {p->parent = g->parent; return connect34(v,p,g,v->Lc,v->Rc,p->Rc,g->Rc);}
        else {v->parent = g->parent;return connect34(p,v,g,p->Lc,v->Lc,v->Rc,g->Rc);}
    }
    else {
        if(IsRChild(*v)) {p->parent = g->parent;return connect34(g,p,v,g->Lc,p->Lc,v->Lc,v->Rc);}
        else {v->parent = g->parent;return connect34(g,v,p,g->Lc,v->Lc,v->Rc,p->Rc);}
    }
}


template <typename T>
BinNode<T>* AVL<T>::insert(const T &e) {

    BinNode<T>* &x = search(e);if(x) return x;
    BinNode<T>* xx = x = new BinNode<T>(e,_hot); _size++;


    for(BinNode<T>* g = _hot;g;g = g->parent) {

        if(!AvlBalance(*g)) {

            FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else updateHeight(g);

    }
    return xx;
}
#endif //_AVL_H
