#include <cstdlib>

int partition(int A[],int lo,int hi) {
    
    int loc = lo + rand() % (hi - lo + 1);
    int temp = A[lo];A[lo] = A[loc];A[loc] = temp;

    int pivot = A[lo];

    while(lo < hi) {

        while(lo < hi){
            if(pivot < A[hi]) hi--;
            else { A[lo++] = A[hi]; break; }
        }

        while(lo < hi){
            if(pivot > A[lo]) lo++;
            else { A[hi--] = A[lo]; break; }
        }
    }

    A[lo] = pivot;
    return lo;
}

void quickSort(int* A,int lo,int hi) {
    
    if(hi-lo < 2) return;
    int mid = partition(A,lo,hi-1);
    quickSort(A,lo,mid);
    quickSort(A,mid+1,hi);
}

void quickSort(int* A,int n) {
    quickSort(A,0,n);
}


