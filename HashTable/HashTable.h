//
// Created by tianbao on 17-12-3.
//

#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <cstddef>
#include <cstring>
#include <climits>
#include <iostream>
#include <string>
#include <functional>
#include "Entry.h"
using std::memset;
using std::string;
using std::hash;

template <typename K,typename V>
class HashTable {

public:

    //构造函数
    HashTable();
    HashTable(int initialCapacity, float loadFactor = 0.75f);
    HashTable(const HashTable<K,V>& e);
    ~HashTable();

    //功能函数
    void clear();
    V get(K) const;
    bool isEmpty() const {return _size == 0;}
    V put(K,V);
    bool remove(K);
    int size() const {return _size;}
    int max_size() {return capacity;}
    V& operator[] (const K& key);

private:

    //默认量
    const int DEFAULT_INITIAL_CAPACITY = 16;//默认初始容量
    const int MAXIMUM_CAPACITY = 1 << 30;//最大容量
    const float DEFAULT_LOAD_FACTOR = 0.75f;//默认的加载因子

    //需要直接初始化的量
    int threshold;//threshold = 容量*加载因子，用来判断是否需要h调整HashTable容量
    int capacity;//table数组的容量
    float LoadFactor;//加载因子实际的大小
    int _size = 0;//键值对的数量
    Entry<K,V>** table;//哈希表

    //私有的功能函数
    int indexFor(int h, int length) const {return h%length;}//返回索引值，保证返回值小于length
    void resize(int);

    //求哈希码函数
    static int hash(int key) //预处理hash值，避免较差的离散hash序列，导致桶没有充分利用
    {
        return 31*key+2;
    }
    static size_t hashCode(char e) { return (size_t)e;}
    static size_t hashCode(short e) { return (size_t)e;}
    static size_t hashCode(bool e) { return (e)?1:0;}
    static size_t hashCode(int e) {return (size_t)e;}
    static size_t hashCode(long e) {return (size_t)((e>>32)+(int)e);}
    static size_t hashCode(long long e) {return (size_t)((e>>32)+(int)e);}
    static size_t hashCode(double e) {
        if(e == 0) return 0;
        return (size_t )*(int*)(&e);
    }
    static size_t hashCode(float e) {
        if(e == 0) return 0;
        return (size_t )*(int*)(&e);
    }
    static size_t hashCode(string e) {
        int h = 0;
        for(size_t n = e.size(),i = 0;i<n;i++) {h = (h<<5)|(h>>27);h+=(int)e[i];}
        return (size_t)h;
    }

};


template <typename K,typename V>
HashTable<K,V>::HashTable():LoadFactor(DEFAULT_LOAD_FACTOR),capacity(DEFAULT_INITIAL_CAPACITY) {

    threshold = (int)DEFAULT_INITIAL_CAPACITY*DEFAULT_LOAD_FACTOR;
    table = new Entry<K,V>*[DEFAULT_INITIAL_CAPACITY];
    memset(table, 0,sizeof(Entry<K,V>*)*capacity);

}


template <typename K,typename V>
HashTable<K,V>::HashTable(int initialCapacity,float loadFactor) {

    if (initialCapacity > MAXIMUM_CAPACITY || initialCapacity < 0) initialCapacity = MAXIMUM_CAPACITY;
    LoadFactor = loadFactor;

    capacity = 1;
    while (capacity < initialCapacity) capacity <<= 1;//找出大于initialCapacity最大的幂
    table = new Entry<K,V>* [capacity];
    memset(table, 0,sizeof(Entry<K,V>*)*capacity);

    threshold = (int)(capacity * loadFactor);//设置“kHashMap阈值”,当HashMap中存储数据的数量达到threshold时，就需要将HashMap的容量加倍.
}


template <typename K,typename V>
HashTable<K,V>::HashTable(const HashTable<K, V> &e):LoadFactor(e.LoadFactor),_size(e._size),capacity(e.capacity),threshold(e.threshold){

    table = new Entry<K,V>*[capacity];
    memset(table, 0,sizeof(Entry<K,V>*)*capacity);

    for(int j = 0;j<capacity;j++) {

        Entry<K,V>* temp = e.table[j];//一个一个链表的添加
        while(temp!= 0) {

            Entry<K,V>* newEntry = new Entry<K,V>(temp->getKey(),temp->getValue());
            newEntry->next = table[j];
            table[j] = newEntry;
            temp = temp->next;
        }
    }
}


template <typename K,typename V>
HashTable<K,V>::~HashTable() {

    clear();
    delete table;
}


template <typename K,typename V>
void HashTable<K,V>::resize(int newCapacity) {

    if (capacity == MAXIMUM_CAPACITY)  { threshold = INT_MAX;return;}//最大容量了，不允许扩容

    Entry<K,V>** newTable = new Entry<K,V>*[newCapacity];
    memset(newTable, 0,sizeof(Entry<K,V>*)*newCapacity);
    for(int j = 0;j < capacity; ++j) {

        Entry<K,V>* e = table[j];
        table[j] = nullptr;
        //对一条链进行操作
        while(e!= nullptr) {

            Entry<K,V>* next = e->next;
            int h = hash(hashCode(e->getKey()));
            int i = indexFor(h, newCapacity);
            e->next = newTable[i];
            newTable[i] = e;
            e = next;
        }
    }
    delete table;//原来数组的内容直接移植到新数组上面去了，所以只要直接删除原来的数组即可！！！！
    table = newTable;
    capacity = newCapacity;
    threshold = (int)(newCapacity * LoadFactor);

}


template <typename K,typename V>
V HashTable<K,V>::get(K k) const {

    int h = hash(hashCode(k));
    int index = indexFor(h, capacity);
    Entry<K,V>* e = table[index];
    while(e != nullptr) {
        if(k == e->getKey()) return  e->getValue();
        e = e->next;
    }
    V v = V();
    return v;
}


template <typename K,typename V>
V HashTable<K,V>::put(K key,V value) {

    int h = hash(hashCode(key));
    int i = indexFor(h, capacity);
    //测试下标用的语句，可以看到个元素的聚集情况
    //std::cout << "下标为" << i << std::endl;
    //如果对应的键已经存了,将值进行替换即可,不用新建键了
    for(Entry<K,V>* e = table[i];e;e = e->next) {
        if(e->getKey() == key) {
            V oldValue = e->getValue();
            e->setValue(value);
            return  oldValue;
        }
    }

    Entry<K,V>* e = new Entry<K,V>(key,value);
    e->next = table[i];
    table[i] = e;
    if (++_size >= threshold) resize(capacity * 2);
    return e->getValue();
}


template <typename K,typename V>
bool HashTable<K,V>::remove(K key) {

    int h = hash(hashCode(key));
    int i = indexFor(h, capacity);

    Entry<K,V>*prev = table[i];
    Entry<K,V>* e = prev;

    while(e != 0) {

        Entry<K,V>*next = e->next;

        if(e->getKey() == key) {

            _size--;
            if(prev == e) table[i] = next;
            else prev->next = next;
            delete e;
            return true;
        }
        prev = e;
        e = next;
    }
    return false;
}


template <typename K,typename V>
void HashTable<K,V>::clear() {

    _size = 0;
    for(int i = 0;i<capacity;i++) {

        Entry<K,V>* temp = table[i];
        table[i] = nullptr;
        //一条一条链逐个删除
        while(temp!= nullptr){

            Entry<K,V>*next = temp->next;
            delete temp;
            temp = next;
        }
    }
}


template <typename K,typename V>
V& HashTable<K,V>::operator[](const K &key) {

    int h = hash(hashCode(key));
    int index = indexFor(h, capacity);
    Entry<K,V>* e = table[index];
    while(e != nullptr) {
        if(key == e->getKey()) return e->getValue();
        e = e->next;
    }
    put(key,V());
    return operator[](key);
}

#endif //_HASHTABLE_H
