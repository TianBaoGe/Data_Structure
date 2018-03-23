//
// Created by tianbao on 17-9-18.
//

#ifndef _VECTOR_H
#define _VECTOR_H

#include <cstddef>
#include <algorithm>
#include <cstdlib>
#include "Priority_Queue.h"
using std::swap;

#define DEFAULT_CAPACITY 8

template<typename T>
class Vector
{

public:

    //构造函数
    Vector(int num = DEFAULT_CAPACITY, int s = 0, T v = T())
    {
        elem = new T[capacity = num];for (_size = 0;_size < s;elem[_size++] = v);
    }
    Vector(T const*p, int n) { copyFrom(p, 0, n); }
    Vector(T const*p, int lo, int hi) { copyFrom(p, lo, hi); }
    Vector(Vector<T> const& p) { copyFrom(p.elem, 0, p._size); }
    Vector(Vector<T> const& p, int lo, int hi) { copyFrom(p.elem, lo, hi); }
    //析构函数
    ~Vector() { delete[] elem; }
    //只读函数
    int size() const { return _size; }
    bool empty() const { return _size <= 0; }
    int find(const T& e) const { return find(e, 0, _size); }
    int find(const T& e, int lo, int hi) const;
    int search(const T& e) const //有序向量的整体高效查找
    {
        return (_size <= 0) ? -1 : search(e, 0, _size);
    }
    int search(const T& e, int lo, int hi) const;
    //可修改的函数
    T&operator[] (int index) const;
    Vector<T>& operator= (const Vector<T>&);
    void pop_back() { remove(_size - 1); }
    T remove(int index); //删除指定下标元素，并返回删掉的元素
    int remove(int lo, int hi);
    int insert(int index, const T& e);
    int push_back(const T& e)
    {
        return insert(_size, e);
    }
    T& at(int index) { assert:0 <= index<_size;return elem[index]; }
    int Capacity() { return capacity; }

    //各种排序算法
    void quickSort() {quickSort(0,_size-1);}
    void bubbleSort() {int hi = _size;while(!bubbleSort(0,hi--));}
    void heapSort() {heapSort(0,_size);}
    void insertSort() {insertSort(0,_size);}
    void selectSort() {selectSort(0,_size);}


protected:

    int _size; int capacity; T* elem;
    void copyFrom(T const* A, int lo, int hi); //A指向的内容不能修改
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    void quickSort(int lo, int hi);
    bool bubbleSort(int lo,int hi);
    void heapSort(int lo,int hi);
    void insertSort(int lo,int hi);
    void selectSort(int lo,int hi);

};


template <typename T>
void Vector<T>::copyFrom(T const *A, int lo, int hi) //相当于构造函数了，初始化三个基本元素
{
    elem = new T[capacity = (hi - lo) * 2];
    _size = 0;
    while (lo < hi)
    {
        elem[_size++] = A[lo++];
    }
}

8o
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& p)
{
    if (elem) delete[] elem; //释放原有的资源;
    copyFrom(p.elem, 0, p._size);
    return *this;
}


template <typename T>
void Vector<T>::expand()
{
    if (_size < capacity) return;
    if (capacity < DEFAULT_CAPACITY) capacity = DEFAULT_CAPACITY;//容量太小了;
    T* old_elem = elem;
    elem = new T[capacity <<= 1];
    for (int i = 0;i <_size;i++)
    {
        elem[i] = old_elem[i];
    }
    delete[] old_elem;
}


template <typename T>
void Vector<T>::shrink()
{
    if (_size < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > capacity) return; //以25%为界
    T* oldelem = elem;
    elem = new T[capacity >>= 1];
    for (int i = 0;i< _size;++i) elem[i] = oldelem[i];
    delete[] oldelem;
}


template <typename T>
int Vector<T>::find(const T& e, int lo, int hi) const {

    assert: 0 <= lo < hi <= _size;
    while ((lo < hi--) && (e != elem[hi]));
    return hi;//失败的时候返回lo-1
}


template <typename T>
T& Vector<T>::operator[] (int index) const {

    assert: 0 <= index <= _size;
    return elem[index];
}


template <typename T>
int Vector<T>::insert(int index, const T &e) {

    assert:0 <= index <= _size;
    expand();
    for (int i = _size;i>index;i--) elem[i] = elem[i - 1];
    elem[index] = e;_size++;
    return index;
}


template <typename T>
int Vector<T>::remove(int lo, int hi) {

    if (lo == hi) return 0;
    while (hi<_size) elem[lo++] = elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(int index) {

    assert: 0 <= index < _size;
    T e = elem[index];
    remove(index, index + 1);
    return e;
}


template <typename T>
int Vector<T>::search(const T &e, int lo, int hi) const {

    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        if (e < elem[mi]) hi = mi;
        else if (elem[mi] < e) lo = mi + 1;
        else return mi;
    }
    return -1;
}



template <typename T>
void Vector<T>::quickSort(int up, int down) {

    int lo = up,hi = down;
    swap(elem[lo], elem[lo + rand() % (hi - lo + 1)]);
    T pivot = elem[lo];
    while (lo<hi) {
        while (lo<hi) {
            if (pivot < elem[hi]) hi--;
            else { elem[lo++] = elem[hi];break; }
        }
        while (lo < hi) {
            if (elem[lo]<pivot) lo++;
            else { elem[hi--] = elem[lo];break; }
        }
    }

    elem[lo] = pivot;
    if(lo - up > 1) quickSort(up,lo-1);
    if(down - lo > 1) quickSort(lo+1,down);
}


template <typename T>
bool Vector<T>::bubbleSort(int lo, int hi) {

    bool judge = true;
    while(++lo < hi){

        if(elem[lo-1] > elem[lo]) {
            judge  = false;
            swap(elem[lo-1],elem[lo]);
        }
    }
    return judge;
}


template <typename T>
void Vector<T>::heapSort(int lo, int hi) {

    PQueue<T> H(elem+lo,hi-lo);
    while(!H.empty()){
        elem[--hi] = H.top();H.pop();
    }
}


template <typename T>
void Vector<T>::selectSort(int lo, int hi) {

    for(int i = lo;i<hi;i++) {

        T min = elem[i];int loc = i;
        for(int j = i+1;j<hi;j++) if(min > elem[j]) min = elem[j],loc = j;
        swap(elem[i],elem[loc]);
    }
}


template <typename T>
void Vector<T>::insertSort(int lo, int hi) {

    for(int i  = lo+1;i < hi;i++) {

        T temp = elem[i];
       for(int j = i-1;j >= lo;j--) {

           if(elem[j] > temp) elem[j+1] = elem[j];
           else {
               elem[j+1] = temp;break;
           }
       }
    }
}
#endif //_VECTOR

