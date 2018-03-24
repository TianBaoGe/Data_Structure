#include<iostream>
using namespace std;
int binarySearch(int*,int,int);
int main(){

    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int b = binarySearch(a,10,11);
    int c = binarySearch(a,10,5);
    cout << b << " " <<  c << endl;
        return 0;
}

int binarySearch(int* a,int n,int key){

    int low = 0;
    int high = n;
    int mid = 0;

    while(low <= high){
        mid = (high+low)>>1;
        if(a[mid] == key) return mid;
        else if(a[mid] < key) low = mid+1;
        else high = mid -1;
    }

    return -1;
}
