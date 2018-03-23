//
// Created by tianbao on 17-9-17.
//

#include "List.h"

template <typename T>
List<T>::List()
{
    init();
}

template <typename T>
void List<T>::init()
{
    firstNode = new ListNode<T>;
    lastNode = new ListNode<T>;
    firstNode->curr = lastNode; firstNode->pred = nullptr;
    lastNode->curr = nullptr; lastNode->pred = firstNode;
    size = 0;

}

template <typename T>
T& List<T>::operator[] (Index r) const
{
    assert: r>0 && r<size;

    ListNode<T>*p = getFirst();
    while( 0 < r--)
    {
        p = p->curr;
    }

    return p->data;
}

template <typename T>
ListNode<T>* List<T>::find(const T& e,int n,ListNode<T>* p) const //寻找节点p前面等于p的最后一个节点
{
    while(0 < n--)
    {
        if( e == (p = p->pred)->data) return p;
    }

    return nullptr;
}

template<typename T>
ListNode<T>* List<T>::insertFront(ListNode<T>* p,T& e)
{
    return p->insertPred(e);
}

template <typename T>
ListNode<T>* List<T>::insertBehind(ListNode<T>* p,T &e)
{
    return p->inserrCurr(e);
}

template <typename T>
ListNode<T>* List<T>::insertFirst(T &e)
{
    size++;
    return firstNode->inserrCurr(e);
}

template <typename T>
ListNode<T>* List<T>::insertLast(T &e)
{
    size++;
    return firstNode->inserrCurr(e);
}

template <typename T>
T List<T>::remove(ListNode<T> *p)
{
    T temp = p->data;
    p->pred->curr = p->curr;
    p->curr->pred = p->pred;
    delete p;
    size--;
    return temp;
}

template <typename T> //这里只删除了头结点和尾节点之间的元素，因为方便用户自己调用claer()时不会删除头尾节点导致链表失效;
List<T>::~List()
{
    clear();
    delete firstNode;
    delete lastNode;
}

template <typename T>
int List<T>::clear()
{
    int old_size = size;
    while(size >= 0) remove(firstNode->curr); //在这里面size已经发生了变化;
    return old_size;
}

template <typename T>
int List<T>::deduplicate() //删除无序链表中的重复元素,时间复杂度为O(n^2);
{
    if(size < 2) return 0; //链表中只有0个或1个元素，不可能重复
    int old_size = size; //记录原来的链表节点数量
    ListNode<T>* temp = firstNode;
    Index num = 0;
    while((temp = temp->curr) != lastNode)
    {
        ListNode<T>* p = find(temp->data,num,temp);
        p ? remove(p):num++; //如果p为nullptr证明前面并无重复的元素，所以轮到下一个节点继续比较，所以代表前面元素数量的num要++;
    }
    return old_size-size; //返回重复元素的数量
}

template <typename T>
void List<T>::traverse(void (* vist)(T &)) //借助函数指针完成遍历
{
    for(ListNode<T>* temp = firstNode->curr; temp != lastNode; temp = temp->curr)
    {
        vist(temp->data);
    }
}

template <typename T> template <typename VST>
void List<T>::traverse(VST & vist)
{
    for(ListNode<T>* temp = firstNode->curr; temp!=lastNode; temp = temp->curr)
    {
        vist(temp->data);
    }
}

template <typename T>
int List<T>::uniquify() //成批删除重复元素，效率更高，前提是链表已经为有序表
{
    if(size < 2) return 0;
    int old_size = size;
    ListNode<T>* p = getFirst();
    ListNode<T>* q;
    while( (q = p->curr) != lastNode) //这是 q = p->curr;
    {
        if( p->data != q->data) p = q;
        else remove(q);
    }
    return old_size-size;
}

template<typename T> //该方法在已经排好序的前提下效率很高，时间复杂度仅为O(n);
ListNode<T>* List<T>::search(const T &e, int n, ListNode<T> *p) const // 寻找小于等于节点p最大的一个节点
{
    while(n-- >= 0)
    {
       if( (p = p->pred)->data <= e) break;
    }
    return p;
}

template<typename T>
void List<T>::insertSort(ListNode<T>* p , int n) //插入排序，分为两部分，前面一部分按顺序，后面一部分没排序，时间复杂度为O(n^2);
{
    for(int i = 0;i < n; i++)
    {
        insertBehind( search(p->data,i,p), p->data);
        p = p->curr;
        remove(p->pred);
    }
}

template<typename T>//选择排序，把元素按顺序扔到后面去,时间复杂度为O(n^2);
void List<T>::selectSort(ListNode<T>* p, int n)
{
    ListNode<T>* head = p->pred;
    ListNode<T>* tail = p;
    for(int i = 0;i < n;i++) tail = tail->curr;
    while( 1 < n)
    {
        ListNode<T>* max = selectMax(head->curr,n);
        insertFront(tail,remove(max));
        tail = tail->pred;
        n--;
    }
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T> *p, int n) const
{

}