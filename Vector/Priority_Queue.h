//
// Created by tianbao on 17-11-26.
//

#ifndef _PQUEUE_H
#define _PQUEUE_H

#define Inheap(n,i)  (((i)<(n)) && ((i)>-(1)) )
#define Parent(i)  ( (i-1)/2 )
#define LastInternal(n) Parent(n-1) //最后一个内部节点
#define LChild(i) ( i*2 + 1 )
#define RChild(i) ( i*2 + 2 )
#define ParentValid(i) (0<i) //是否存在父母节点
#define LChildValid(n,i) Inheap(n,LChild(i))
#define RChildValid(n,i) Inheap(n,RChild(i))


#include <vector>
#include <iostream>
#include <algorithm>
using std::vector;
using std::swap;
using std::cout;
using std::endl;
using std::max;

template <typename T>
class PQueue{

public:

    PQueue() {}
    PQueue(T* array,int n);
    void push(T);
    bool empty() const {return _elem.empty();}
    int size() const {return _elem.size();}
    T top();
    void pop();

protected:

    vector<T>_elem;
    int percolateDown(int n,int i);
    int percolateUp(int i);
    void heapify(int n);//Floyd建堆算法

};

template <typename T>
T PQueue<T>::top() { return _elem[0];}


template <typename T>
void PQueue<T>::push(T e) {

    _elem.push_back(e);
    percolateUp(_elem.size()-1);//新插入元素，要上滤操作
}


template <typename T>
int PQueue<T>::percolateUp(int i) {

    T temp = _elem[i];
    while(ParentValid(i)) {

        int index = Parent(i);
        if(_elem[index] > temp) break;
        _elem[i] = _elem[index];
        i = index;//必须交换啊儿子
    }
    _elem[i] = temp;
    return i;//返回上滤最终到达位置
}


template <typename T>
void PQueue<T>::pop() {

    _elem[0] = _elem[_elem.size()-1];//替代元素；
    _elem.pop_back();//删除最后一个元素
    percolateDown(_elem.size(),0);

}


template <typename T> //删除元素时的上浮操作
int PQueue<T>::percolateDown(int n, int i) {

    T temp = _elem[i];
    while(true) {

        if(!LChildValid(n,i)) break;
        T max = LChild(i);
        if(RChildValid(n,i)) {max = (_elem[max] > _elem[RChild(i)]) ? max : RChild(i);}
        max = (temp > _elem[max])? i : max;
        if(max == i) break;
        _elem[i] = _elem[max];
        i = max;
    }
    _elem[i] = temp;
    return i;

    //第二种方法，要使用swap
    /*
    int index;
    //如果父母和儿子最大的是父母，就可以停止循环了，数据结构已经调整好
    while( i != (index = ProperParent(_elem,n,i))) {
        swap(_elem[i],_elem[index]);
        i = index;
    }
    return i;
     */
}


template<typename T>
PQueue<T>::PQueue(T* array,int n) {

    for (int i = 0; i < n; ++i) { _elem.push_back(array[i]); }
    heapify(n);
}


template <typename T>
void PQueue<T>::heapify(int n) {

    for(int i = LastInternal(n);Inheap(n,i);i--) percolateDown(n,i);
}
#endif //_QUEUE_PQUEUE_H
