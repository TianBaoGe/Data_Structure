//
// Created by tianbao on 17-9-17.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H
#include "ListNode.h"

template <typename  T> class List
{

private:

    int size;
    ListNode<T>* firstNode;
    ListNode<T>* lastNode;

protected:

    void init(); //链表创建时的初始化
    int clear(); //清楚链表所有节点
    void CopyNode(ListNode<T>*, int); //复制链表子自位置P起的n项
    void merge(ListNode<T> *&,int,List<T>&,ListNode<T>*,int); //归并
    void mergeSort(ListNode<T>*&,int); //归并排序
    void selectSort(ListNode<T>*,int); //选择排序
    void insertSort(ListNode<T>*,int); //插入排序

public:

//构造函数
    List(); //默认构造函数
    //List(const List<T>& temp); //复制构造函数
    //List(ListNode<T>*p ,int n);//从链表的p开始复制n项
// 析构函数
    ~List();
//只读函数
    Index getSize() const { return size;}
    bool empty() const { return size <= 0;}
    T& operator[] (Index r) const;
    ListNode<T>* getFirst() const { return firstNode->curr; }
    ListNode<T>* getLast() const { return lastNode->pred; }
    bool valid (ListNode<T>* p) const //判断节点是否合法
    {
        return p && (p != firstNode) && (p!= lastNode);
    }
    int disordered() const;//判断链表是否已经排序
    ListNode<T>* find(const T& e) const //无序查找
    { return find(e, size , lastNode);}
    ListNode<T>* find(const T& e,int n,ListNode<T>* p) const;
    ListNode<T>* search(const T& e) const //有序查找
    { return search(e, size, lastNode); }
    ListNode<T>* search(const T& e,int n,ListNode<T>* p) const;
    ListNode<T>* selectMax(ListNode<T>* p,int n) const; //从p开始往后n个节点寻找最大的节点
    ListNode<T>* selectMax() const
    { return selectMax( firstNode->curr, size);}
//可写函数
    ListNode<T>* insertFirst(T& e);
    ListNode<T>* insertLast(T& e);
    ListNode<T>* insertFront(ListNode<T>* p,T& e);
    ListNode<T>* insertBehind(ListNode<T>* p,T& e);
    T remove(ListNode<T>* p);
    void merge(List<T>& p)
    { merge(firstNode->curr, size, p, p.getFirst(), p.getSize());}
    void sort(ListNode<T>* p,int n);
    void sort()
    { sort(getFirst(),size);}
    int deduplicate(); //无序去掉重复元素
    int uniquify(); //有序去掉重复元素
    void reverse(); //链表前后颠倒
    //遍历
    void traverse( void(*) (T&));
    template <typename VST> void traverse(VST&);


};


#endif //LIST_LIST_H
