#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>
using std::string;
using std::fstream;
using std::cin;

int main() {

/*
    string route;
    cin >> route;
    fstream inFile(route);
    assert(inFile.is_open());

    Graph<char,int> myGraph;

    int V_num,E_num;
    int choose = 1;
    inFile >> V_num >> E_num;
    inFile >> choose;

    for(int i = 0;i<V_num;i++) {

        char temp;
        inFile >> temp;
        myGraph.insert(temp);
    }

    for(int i = 0;i<E_num;i++) {

        char head,tail;
        inFile >> head >> tail;
        int H = myGraph.location(head);
        int T = myGraph.location(tail);
        myGraph.insert(0,0,H,T);
    }
    inFile.close();


    cout << "广度搜索为：" << endl;
    myGraph.bfs(0);
    cout << endl;
    cout << "深度搜索为：" << endl;
    myGraph.dfs(0);

    cout << "最小生成树为：" << endl;
    //myGraph.prim_1(0);
    cout << endl;
    myGraph.prim_2(0);
    cout << endl << endl;
    cout << "最短路径为：" << endl;
    myGraph.dijkstra(0);
*/

    Graph<int,int> a;
    a.insert(0);
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    a.insert(6);
    a.insert(4,3,0,1);
    a.insert(4,7,0,2);
    a.insert(4,5,0,3);
    a.insert(4,6,1,4);
    a.insert(4,2,1,2);
    a.insert(4,3,2,4);
    a.insert(4,3,2,3);
    a.insert(4,2,3,5);
    a.insert(4,8,3,6);
    a.insert(4,2,4,6);
    a.insert(4,2,5,6);

    cout << "广度搜索为：" << endl;
    a.bfs(0);
    cout << endl;
    cout << "深度搜索为：" << endl;
    a.dfs(0);



    cout << "最小生成树为：" << endl;
    a.prim_1(0);
    cout << endl;
    a.prim_2(0);
    cout << endl << endl;
    cout << "最短路径为：" << endl;
    a.dijkstra(0);
}