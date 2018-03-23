//
// Created by tianbao on 17-9-17.
//
#include "ListNode.h"

template <typename T>
ListNode<T>* ListNode<T>::inserrCurr(const T &e) //在节点后面插入新节点
{
    ListNode<T>* temp = new ListNode(e,this,curr);
    curr->pred = temp;
    curr = temp;
    return temp;
}

template <typename T>
ListNode<T>* ListNode<T>::insertPred(const T &e) //在节点前面插入新节点
{
    ListNode<T>* temp = new ListNode(e,pred,this);
    pred->curr = temp;
    pred = temp;
    return temp;
}