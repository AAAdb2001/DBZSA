#include<iostream>
#include<omp.h>
#include <bits/stdc++.h>
using namespace std;
// void swap(int &a,int &b){
	
// 	int temp;
// 	temp=a;
// 	a=b;
// 	b=temp;
// }
void bubble_sort_parallel(int arr[],int n){
    double start_time = omp_get_wtime();
    for(int i=0;i<n-1;i++){
        #pragma omp parallel for num_threads(1000)
        for(int j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
    double end_time = omp_get_wtime();
    cout<<"Time require for parallel execution is "<<end_time - start_time<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}
void bubble_sort_serial(int arr[],int n){
    double start_time = omp_get_wtime();
    #pragma omp parallel  num_threads(1000)
    for(int i=0;i<n-1;i++){
        #pragma omp critical
        for(int j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
    double end_time = omp_get_wtime();
    cout<<"Time require for serial execution is "<<end_time - start_time<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}
int main(){
    int arr[] = {8,5,7,3,2};
    int n = 5;
    bubble_sort_serial(arr,n);
    bubble_sort_parallel(arr,n);
    return 0;
}