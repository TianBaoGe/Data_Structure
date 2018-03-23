#include <iostream>
#include "Graph.h"
#include <string>
#include <fstream>
#include<stdio.h>
#include<string.h>
using namespace std;

int Main() {

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


    return 0;
}

int main()
{
    int find(char *ss[],char *p,int len);
    int i,len;scanf("%d",&len);
    char *ss[len] ,*obj;

    char **a = ss;
    for(i=0;i<len;i++)
        gets(*(ss+i));
    gets(obj);
    printf("%d\n",find(ss,obj,len));
    return 0;
}
int find(char *ss[],char *p,int len)
{
    int i,l=strlen(p),j;
    for(i=0;i<len;i++)
    {
        if(strlen(*(ss+i))!=l) continue;
        for(j=0;j<l;j++)
        {
            if(*(*(ss+i)+j)!=*(p+j)) continue;return i;
        }
    }
}