#include <iostream>
#include "Vector.h"
using namespace std;

int main() {

    Vector<int>a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(10);
    a.push_back(7);
    a.push_back(25);
    a.push_back(100);
    a.push_back(3);

    //int a[] = {1,2,10,7,25,100,3};

    for(int i = 0;i<a.size();++i) {cout << a[i] << endl;}
    cout << "排序后："<< endl;

    a.insertSort();

    for(int i = 0;i<a.size();++i) {cout << a[i] << endl;}


 }