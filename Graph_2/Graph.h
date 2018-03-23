//
// Created by tianbao on 17-12-16.
//

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include "Vertex.h"
#include "UFSets.h"
#include "MSTEdge.h"
#include <stack>
#include <cstring>
#include <cassert>
#include <queue>

#include <iostream>
using std::cout;
using std::endl;

using std::vector;
using std::stack;
using std::memset;
using std::queue;
using std::priority_queue;

template <typename V,typename E>
class Graph {

public:

    //构造函数
    Graph() {Edge_num = 0;}

    //功能函数
    V& vertex(int i) {assert(i>=0&&i<table.size());return table[i].data;}
    int inDegree(int i) const {assert(i>=0&&i<table.size());return table[i].inDegree;}
    int outDegree(int i) const { assert(i>=0&&i<table.size());return table[i].outDegree; }
    int numOfVertex() const {return table.size();}
    int numOfEdge() const {return Edge_num;}
    void insert(const V& v);
    bool remove(int i);
    Edge<E>* exist(int i,int j) const;
    int& weigiht(int i,int j);
    void insert(const E&e,int w,int i,int j);
    bool remove(int i,int j);
    int location(V data) const;

    void bfs(int);//广度优先
    void dfs(int);//深度优先
    stack<V>* tSort(int);//拓扑排序
    void prim_1(int);//最小支撑树
    void prim_2(int);
    void dijkstra(int);//最短路径

private:

    vector<Vertex<V,E>> table;
    int Edge_num;

    Edge<E>* firstNbr(int i)const;
    Edge<E>* nextNbr(Edge<E>*) const;
    void dfs(int v,bool*,int&);
};


template <typename V,typename E>
Edge<E>* Graph<V,E>::firstNbr(int index) const {

    if(table[index].next)return table[index].next;
    return nullptr;
}


template <typename V,typename E>
int Graph<V,E>::location(V data) const {

    for(int i = 0;i<table.size();i++) if(table[i].data == data) return i;
    return -1;
}


template <typename V,typename E>
Edge<E>* Graph<V,E>::nextNbr(Edge<E>* e) const {

    if(!e) return nullptr;
    return e->next;
}


template <typename V,typename E>
int& Graph<V,E>::weigiht(int i, int j) {

    Edge<E>* temp =  table[i].next;
    while(temp) {
        if(temp->tail == j) return temp->wegiht;
        temp = temp->next;
    }
}


template <typename V,typename E>
void Graph<V,E>::insert(const V &v) {

    table.push_back(Vertex<V,E>(v));
}

template <typename V,typename E>
bool Graph<V,E>::remove(int i) {

    if(i>=table.size() || i <0) return false;

    for(int j = 0;j<table.size();j++) {
        Edge<E>*first = table[j].next;
        Edge<E>* second = first;
        while(second) {

            if(second->tail == i){
                first = second->next;
                //delete second;
                Edge_num--;
                break;
            }

            first = second;
            second = second->next;
        }
    }

    Edge<E>* temp = table[i].next;
    while(temp){
        Edge<E>* n = temp->next;
        Edge_num--;
        delete temp;
        temp = temp->next;
    }
    auto it = table.begin();
    table.erase(it+i);
    return true;
};


template <typename V,typename E>
Edge<E>* Graph<V,E>::exist(int i, int j) const {

    if(i>=table.size() || i <0) return nullptr;

    Edge<E>* temp = table[i].next;

    while(temp) {
        if(temp->tail == j) return temp;
        temp = temp->next;
    }
    return nullptr;
}


template <typename V,typename E>
void Graph<V,E>::insert(const E &e, int w,int i, int j) {

    if(exist(i,j)) return;//确保该边不存在
    Edge<E>* n = new Edge<E>(e,j,w,table[i].next);
    table[i].next = n;
    Edge_num++;
}


template <typename V,typename E>
bool Graph<V,E>::remove(int i, int j) {

    Edge<E>* a = table[i].next;
    Edge<E>* b = a;
    while(b) {

        if(b->tail == j) {
            a->next = b->next;
            delete b;
            Edge_num--;
            return true;
        }
        a = b;
        b = a->next;
    }
    return false;
}


template <typename V,typename E>
void Graph<V,E>::bfs(int start) {

    if(table.size() == 0 || start<0 || start >= table.size()) return;

    assert(start>=0 && start<table.size());

    int num = 0;//遍历的个数；
    int* judge = new int[table.size()];
    //memset(judge,0,sizeof(judge));
    for(int i = 0;i < table.size();i++) judge[i] = 0;
    judge[start] = 1;

    queue<int> Q;Q.push(start);
    while(num != table.size()) {

        int S;

        if(Q.empty()) {
            for(int i = 0;i<table.size();i++) if(!judge[i]) {judge[i] = 1;Q.push(i);break;}
        }

        S = Q.front();
        Q.pop();
        Vertex<V,E>& temp = table[S];
        int next = S;
        //遍历要执行的操作，可自己改动
        cout << temp.data << endl;
        num++;
        Edge<E>* e_next = firstNbr(S);
        if(e_next)next = e_next->tail;
        while(e_next) {

            if(!judge[next]) {
                judge[next] = 1;
                Q.push(next);
            }
            e_next = e_next->next;
            if(e_next) next = e_next->tail;
        }
    }
   delete[] judge;
}

template <typename V,typename E>
void Graph<V,E>::dfs(int start) {

    if(table.size() == 0 || start<0 || start >= table.size()) return;

    bool* judge = new bool[table.size()];
    //memset(judge,0,sizeof(judge));
    for(int i = 0;i < table.size();i++) judge[i] = false;
    judge[start] = true;

    int n = 0;
    while(n != table.size()) {
        dfs(start,judge,n);
        for(int i = 0;i<table.size();i++)  if(!judge[i]) {start = i;}
    }
    delete[] judge;
}


template <typename V,typename E>
void Graph<V,E>::dfs(int v, bool* judge,int& num) {

    //进行操作
    cout << table[v].data << endl;
    int w;

    judge[v] = 1;num++;
    Edge<E>* e_next = firstNbr(v);
    if(e_next)w = e_next->tail;
    while(e_next) {
        if(!judge[w]) dfs(w,judge,num);
        e_next = e_next->next;
        if(e_next)w = e_next->tail;
    }
}


template <typename V,typename E>//基于边的,只看边的大小，不看方向，方便很多
void Graph<V,E>::prim_1(int start) {

    int n = table.size();
    priority_queue<MSTEdge> PQ;
    UFSets F(n);

    for(int i = 0;i<n;i++) {

        Edge<E>* temp = table[i].next;
        while(temp) PQ.push(MSTEdge(i,temp->tail,temp->wegiht)),temp = temp->next;
    }

    int num = 0;
    while(num != n-1){

        MSTEdge temp = PQ.top();PQ.pop();
        int u = F.Find(temp.head);
        int v = F.Find(temp.tail);
        if(u!=v) {
            F.Union(u, v);//这里必须为u和v,这里的设定本来就是头结点加头结点，最大一个为负数想加，两个孩子节点想家肯定很大几率出现问题
            cout << "（" << temp.head << "," << temp.tail << ")" << endl;//测试用
            num++;
        }
    }
}


template <typename V,typename E>//基于点的
void Graph<V,E>::prim_2(int start) {

    int *judge = new int[table.size()];
    //memset(judge, 0, sizeof(judge));
    for(int i = 0;i < table.size();i++) judge[i] = 0;
    int n = table.size();
    priority_queue<MSTEdge> PQ;
    int num = 1;
    judge[start] = 1;

    do {

        int w;
        Edge<E>* e_next = firstNbr(start);
        if(e_next)w = e_next->tail;
        while(e_next){
            if(!judge[w]) PQ.push(MSTEdge(start,w,e_next->wegiht));
            e_next = e_next->next;
            if(e_next)w = e_next->tail;
        }

        //因为是有向图，求最小生成树要求是无向图，所以只能检查两个方向
        for(int i = 0;i<n;i++){
            Edge<E>* temp = exist(i,start);
            if(temp && !judge[i]) PQ.push(MSTEdge(start,i,temp->wegiht));
        }

        while(!PQ.empty() && num != n) {
            MSTEdge temp = PQ.top();PQ.pop();
            if(!judge[temp.tail]) {
                judge[temp.tail] = 1;
                start = temp.tail;
                cout << "（" << temp.head << "," << temp.tail << ")" << endl;//测试用
                num++;break;
            }
        }

    }while(num != n);
}


class tempV {

public :

    int num;
    int route;
    tempV(int n,int r= 0):num(n),route(r){}
    bool operator< (const tempV& e) const {return route>e.route;}
};


template <typename V,typename E>
void Graph<V,E>::dijkstra(int start) {

    int n = table.size();
    bool* judge = new bool[n];
    //memset(judge, 0, sizeof(judge));
    for(int i = 0;i < table.size();i++) judge[i] = false;

    priority_queue<tempV> PQ;PQ.push(tempV(start));
    int num = 0;

    int w = 0;int s = start;

    while(num != n) {

        tempV temp = PQ.top();
        PQ.pop();
        start = temp.num;

        //这里再次判断因为一个点可能多次放入，可能之前的点多次连接到这个点，可能这个点走完了，但堆里面还有残存的
        if (!judge[start]) {
            judge[start] = true;
            num++;
            cout << s << "到" << start << "最短距离为：" << temp.route << endl;

            Edge<E>* e_next = firstNbr(start);
            if(e_next)w = e_next->tail;

            while (e_next) {
                if (!judge[w])
                    PQ.push(tempV(w, temp.route + e_next->wegiht));
                e_next = nextNbr(e_next);
                if(e_next)w = e_next->tail;
            }
        }
    }
}

#endif //_GRAPH_H
