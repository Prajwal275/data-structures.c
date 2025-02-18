#include <stdio.h>
int main()
{
    int arr[5]={1,2,3,4,5};
    int ele=3;
    int low=0, high=4, mid;
    while (low<=high){
      mid=(low+high)/2;
      if(arr[mid]==ele){
        printf("element found");
      }
      else if(ele<arr[mid]){
        high=mid-1;
      }
      else {
        low=mid+1;
      }
    }
    if(arr[mid]!=ele){
      printf("not found");
    }
 } 
 
