//
// Created by tianbao on 17-11-11.
//

#ifndef _BINTREE_H
#define _BINTREE_H

#include "BinNode.h"
#include <algorithm>
#include <stack>
#include <iostream>
using std::max;
using std::stack;

template <typename T>
class BinTree
{
public:

    BinTree(BinNode<T>* root = nullptr):_root(root){}
    ~BinTree() {clear(_root);}
    BinNode<T>* root() const {return _root;}//不知道表现的行为是否符合预期
    BinNode<T>* insertAsRoot (const T& e);
    BinNode<T>* attachAsLTree (BinNode<T>* x ,BinTree<T>*& t);//T作为x的左子树插入
    BinNode<T>* attachAsRTree (BinNode<T>* x ,BinTree<T>*& t);//T作为x的右子树插入

protected:

    BinNode<T>* _root;
    void clear(BinNode<T>*root){
       if(!root) return;
       clear(root->Lc);
       clear(root->Rc);
       delete root;
    }

};


template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot (const T& e){

    _root = new BinNode<T>;
    _root->data = e;
    return _root;
}


template <typename T> //因为要将T树置空，所以必须传入该树根节点的引用
BinNode<T>* BinTree<T>::attachAsLTree (BinNode<T>* x ,BinTree<T>* &t) {

    if(x->Lc = t->_root) x->Lc->parent = x;//子树的父母置为x,彻底连接子树
    //连接好子树后，更新T树
    t->_root = nullptr;
    return x;
}

template <typename T> //因为要将T树置空，所以必须传入该树根节点的引用
BinNode<T>* BinTree<T>::attachAsRTree (BinNode<T>* x ,BinTree<T>* &t) {

    if(x->Rc = t->_root) x->Rc->parent = x;//子树的父母置为x,彻底连接子树
    //连接好子树后，更新T树
    t->_root = nullptr;
    delete t;//彻底删除该树
    return x;
}

#endif