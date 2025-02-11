#include <stdio.h>
int main(){
    int arr[5]={1,3,2,4,5};
    int ele=4;
    for(int i=0;i<=4;i++){
        if(ele==arr[i]){
            printf("%d",i);
        }
    }
}
