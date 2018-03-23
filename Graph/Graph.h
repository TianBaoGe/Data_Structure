//
// Created by tianbao on 17-12-15.
//

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"
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
    Graph() {
        Edge_num = 0;
    }
    ~Graph() {
        for(int i  = 0;i<Vertex_Array.size();i++)
            for(int j = 0;j<Vertex_Array.size();j++)
                delete Edge_Array[i][j];
    }

    //基本操作函数了
    V& vertex(int i) {assert(i>=0&&i<Vertex_Array.size());return Vertex_Array[i].data;}
    int inDegree(int i) const {assert(i>=0&&i<Vertex_Array.size());return Vertex_Array[i].inDegree;}
    int outDegree(int i) const { assert(i>=0&&i<Vertex_Array.size());return Vertex_Array[i].outDegree; }
    int numOfVertex() const {return Vertex_Array.size();}
    int numOfEdge() const {return Edge_num;}
    void insert(const V& v);
    bool remove(int i);
    bool exist(int i,int j) const;
    int& weigiht(int i,int j) {return Edge_Array[i][j]->weight;}
    void insert(const E&e,int w,int i,int j);
    bool remove(int i,int j);
    int location(V data) const;

    void bfs(int) const ;//广度优先
    void dfs(int) const ;//深度优先
    stack<V>* tSort(int);//拓扑排序
    void prim_1(int);//最小支撑树
    void prim_2(int);
    void dijkstra(int);//最短路径


private:

    vector<Vertex<V>> Vertex_Array;
    vector<vector<Edge<E>*>> Edge_Array;//边都是指针类型
    int Edge_num;

    int firstNbr(int i)const;
    int nextNbr(int i,int j) const;

    void dfs(int v,bool*,int&) const ;

};


template <typename V,typename E>
int Graph<V,E>::location(V data) const {

    for(int i = 0;i<Vertex_Array.size();i++) if(Vertex_Array[i].data == data) return i;
    return -1;
}


template <typename V,typename E>
int Graph<V,E>::firstNbr(int index) const {

    for(int i = 0;i<Edge_Array[index].size();i++) {
        if(Edge_Array[index][i] != nullptr) return i;
    }
    return -1;
}


template <typename V,typename E>
int Graph<V,E>::nextNbr(int index,int loc) const {

    for(int i = index+1;i<Edge_Array[loc].size();i++) {
        if(Edge_Array[loc][i] != nullptr) return i;
    }

    return -1;
}


template <typename V,typename E>
void Graph<V,E>::insert(const V &v) {

    Vertex_Array.push_back(Vertex<V>(v));

    for(int i = 0;i<Edge_Array.size();i++) Edge_Array[i].push_back(nullptr);
    Edge_Array.push_back(vector<Edge<E>*>(Vertex_Array.size()));
}


template <typename V,typename E>
bool Graph<V,E>::remove(int i) {

    if(i>=Vertex_Array.size() || i <0) return false;
    auto it_1 = Vertex_Array.begin();
    Vertex_Array.erase(it_1+i);

    for(int j = 0;j<Edge_Array[i].size();j++) delete Edge_Array[i][j];
    auto it_2 = Edge_Array.begin();
    Edge_Array.erase(it_2+i);

    for(int j = 0;j<Vertex_Array.size();j++) {
        if(Edge_Array[j][i] != nullptr ) Vertex_Array[j].inDegree -= 1,Edge_num--;
        auto it_3 = Edge_Array[j].begin();
        Edge_Array[j].erase(it_3+i);
    }


    return true;
}


template <typename V,typename E>
bool Graph<V,E>::exist(int i, int j) const {

    return (i<Vertex_Array.size()&&i>=0&&j>=0&&j<Vertex_Array.size() && Edge_Array[i][j]);

}


template <typename V,typename E>
void Graph<V,E>::insert(const E &e, int w,int i, int j) {

    if(exist(i,j)) return;//确保该边不存在
    Edge_Array[i][j] = new Edge<E>(e,w);
    Vertex_Array[i].inDegree++;
    Vertex_Array[j].outDegree++;
    Edge_num++;
}


template <typename V,typename E>
bool Graph<V,E>::remove(int i, int j) {

    if(!exist(i,j)) return false;
    delete Edge_Array[i][j];Edge_Array[i][j] = nullptr;
    Vertex_Array[i].inDegree--;
    Vertex_Array[j].outDegree--;
}


template <typename V,typename E>
void Graph<V,E>::bfs(int start) const {

    if(Vertex_Array.size() == 0 || start<0 || start >= Vertex_Array.size()) return;

    assert(start>=0 && start<Vertex_Array.size());

    int num = 0;//遍历的个数；
    int* judge = new int[Vertex_Array.size()];
    //memset(judge,0,sizeof(judge));
    for(int i = 0;i<Vertex_Array.size();i++) judge[i] = 0;
    judge[start] = 1;

    queue<int> Q;Q.push(start);
    while(num != Vertex_Array.size()) {

        int S;
        if(Q.empty()) {
            for(int i = 0;i<Vertex_Array.size();i++) if(!judge[i]) {judge[i] = 1;Q.push(i);break;}
        }

        S = Q.front();
        Q.pop();
        Vertex<V> temp = Vertex_Array[S];
        int next = S;
        //遍历要执行的操作，可自己改动
        cout << temp.data << endl;
        num++;
        next = firstNbr(S);
        while(next!=-1) {

            if(!judge[next]) {
                judge[next] = 1;
                Q.push(next);
            }
            next = nextNbr(next, S);
        }
    }
    delete[] judge;
}


template <typename V,typename E>
void Graph<V,E>::dfs(int start) const {

    if(Vertex_Array.size() == 0 || start<0 || start >= Vertex_Array.size()) return;

    bool* judge = new bool[Vertex_Array.size()];
    memset(judge,0,sizeof(judge));//judge[start] = 1;
    int n = 0;
    while(n != Vertex_Array.size()) {
        dfs(start,judge,n);
        for(int i = 0;i<Vertex_Array.size();i++)  if(!judge[i]) {start = i;break;}
    }
    delete[] judge;
}


template <typename V,typename E>
void Graph<V,E>::dfs(int v, bool* judge,int& num) const {

    //进行操作
    cout << Vertex_Array[v].data << endl;
    judge[v] = 1;num++;
    int w = firstNbr(v);
    while(w!=-1) {
        if(!judge[w]) dfs(w,judge,num);
        w = nextNbr(w,v);
    }
}


template <typename V,typename E>//基于边的
void Graph<V,E>::prim_1(int start) {

    int n = Vertex_Array.size();
    priority_queue<MSTEdge> PQ;
    UFSets F(n);

    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++) {
            if(Edge_Array[i][j]) PQ.push(MSTEdge(i,j,Edge_Array[i][j]->wegiht));
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

    int *judge = new int[Vertex_Array.size()];
    //memset(judge, 0, sizeof(judge));
    for(int i = 0;i<Vertex_Array.size();i++) judge[i] = false;
    int n = Vertex_Array.size();
    priority_queue<MSTEdge> PQ;
    int num = 1;
    judge[start] = 1;

    do {

        int w = firstNbr(start);
        while(w != -1){
            if(!judge[w]) PQ.push(MSTEdge(start,w,Edge_Array[start][w]->wegiht));
            w = nextNbr(w,start);
        }

        //因为是有向图，求最小生成树要求是无向图，所以只能检查两个方向
        for(int i = 0;i<n;i++){
            if(Edge_Array[i][start] && !judge[i]) PQ.push(MSTEdge(start,i,Edge_Array[i][start]->wegiht));
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

    int n = Vertex_Array.size();
    bool* judge = new bool[n];
    memset(judge, 0, sizeof(judge));

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
            w = firstNbr(start);
            while (w != -1) {
                if (!judge[w])
                    PQ.push(tempV(w, temp.route + Edge_Array[start][w]->wegiht));
                w = nextNbr(w, start);
            }
        }
    }
}



#endif //_GRAPH_H
