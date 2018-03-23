//
// Created by tianbao on 17-11-30.
//
#include "AVL.h"

int main() {

    AVL<int> test;
    test.insert(1);
    test.insert(2);
    test.insert(4);
    test.insert(300);
    test.insert(200);

    test.show();
    return 0;
}