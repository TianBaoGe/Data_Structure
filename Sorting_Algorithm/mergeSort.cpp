#include<iostream>
using namespace std;
void mergeArray(int* a,int first,int mid,int last,int* temp){

    int i = first,j = mid+1;
    int loc = 0;

    while(i<=mid && j<=last) {
        if(a[i]<a[j]) temp[loc++]=a[i++];
        else temp[loc++]=a[j++];
    }
    while(i<=mid) temp[loc++] = a[i++];
    while(j<=last) temp[loc++] = a[j++];

    for(int o = 0;o < loc;o++) a[first+o] = temp[o];
}

void mergeSort(int* a,int first,int last,int* temp){

    if(first >= last) return;

    int mid = (first+last)>>1;
    mergeSort(a,first,mid,temp);
    mergeSort(a,mid+1,last,temp);
    mergeArray(a,first,mid,last,temp);
}

void mergeSort(int* a,int n){

    int* temp = new int[n];
    mergeSort(a,0,n-1,temp);
    delete[] temp;
}

int main(){
    int a[] = {10,9,8,7,6,5,4,3,2,1};
    mergeSort(a,10);
    for(int e:a) cout << e << " ";
    cout << endl;
    return 0;
}
