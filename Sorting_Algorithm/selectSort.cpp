void selectSort(int* a,int n){

    for(int i = 0;i < n-1;i++){

        int min = a[i];
        int index = i;
        for(int j = i+1;j < n;j++) if(a[j] < min) min = a[j],index = j;
        
        if(index!=i) min = a[i],a[i] = a[index],a[index]=min;
        }
}
