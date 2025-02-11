#include <stdio.h>

int main() {
    // Write C code here
    int arr[5]={1,2,3,4,5};
    for(int j=0;j<=3;j++){
    for(int i=0;i<=3;i++){
        if (arr[i]>arr[i+1]){
            int temp = arr[i];
            arr[i]=arr[i+1];
        }
    }    
    }for (int i=0; i<=4; i++){ 
    printf("%d",arr[i]);
    }
    return 0;
}
