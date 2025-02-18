#include <stdio.h>
int main()
{
    int arr[5]={2,3,4,10,5};
    int k;
    for(int i=1;i<=4;i++){
     int temp=arr[i];
     k=i;
      for(int j=i-1;j>=0;j--){
        if (arr[j]>temp){
          arr[j+1]=arr[j];
        }
        else {
          break;
        }
        k=j ;
      }
      arr[k]=temp ;
    }
    for(int i=0;i<=4;i++){
      printf(" %d ", arr[i]);
    }
}
