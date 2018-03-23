//
// Created by tianbao on 17-9-17.
//

#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H

typedef int Index;

template <typename T> class ListNode
{
public:
    T data;
    ListNode<T>* pred;
    ListNode<T>* curr;

    ListNode(){} //针对链表的头结点和尾节点
    ListNode(T e, ListNode<T>*p = nullptr, ListNode<T>*c = nullptr):data(e),pred(p),curr(c){}

    ListNode<T>* insertPred(const T& e);
    ListNode<T>* inserrCurr(const T& e);
};




#endif //LIST_LISTNODE_H
