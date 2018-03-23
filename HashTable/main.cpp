#include <iostream>
#include <string>
#include "HashTable.h"
using namespace std;

int main() {

    HashTable<int, int> a(64);

    cout << "大小为：" << a.max_size() << endl;
    a.put(1,2);
    a.put(2, 3);
    a.put(3,4);
    a.put(30, 4);
    a.put(4, 5);
    a.put(11, 20);
    a.put(13,13);
    cout << endl << endl;
    cout << a[2] << endl;
    cout << "个数为：" << a.size() << endl;
    a.remove(2);
    cout << "个数为：" << a.size() << endl;
    cout << a[2] << endl;
    cout << "个数为：" << a.size() << endl;

    return 0;
}