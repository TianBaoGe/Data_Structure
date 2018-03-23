//
// Created by tianbao on 17-12-16.
//

#ifndef _UFSETS_H
#define _UFSETS_H

class UFSets {

public:

    UFSets(int sz = 10) {
        size = sz;
        parent = new int[size];
        for(int i = 0;i<sz;i++) parent[i] = -1;
    }
    ~UFSets() {delete[] parent;}
    void Union(int a,int b) {
        /*
        int r1 = Find(a),r2 = Find(b);
        int temp = r1+r2;
        if(r1 < r2) parent[r2] = r1,parent[r1] = temp;
        else parent[r1] = r2,parent[r2] = temp;
         */
        parent[a] += parent[b];
        parent[b] = a;
    }
    int Find(int x) {
        while(parent[x] >= 0) x = parent[x];
        return x;
    }

private:

    int *parent;
    int size;
};
#endif //_UFSETS_H
