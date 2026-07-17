#include <bits/stdc++.h>
using namespace std;

void bubble_sort(int arr[], int n){
    if (n==1) return;
    int didSwap = 0;

    for(int j =0; j<=n-2; j++){
        if(arr[j]>arr[j+1]){
            int temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
            didSwap = 1;
        }
    }

    if (didSwap == 0) return;

    bubble_sort(arr, n-1);
}

int main() {
    int n;
    cin>>n;
    int arr[n];
    for(int i =0; i<n; i++){
        cin>>arr[i];
    }
    bubble_sort(arr, n);
    for(int i =0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}