#include<stdio.h>
int push(int arr[],int top,int size){
  int num;
  printf("enter the number: ");
  scanf("%d",&num);
  if(size == top){
    printf("stack is full!\n");
  }
  else{
    arr[top]=num;
    top+=1;
  }
  return top;
}
int pop(int arr[],int top){
  if(top==0){
    printf("stack is empty!");
  }
  else{
    arr[top -1]=0;
    top-=1;
  }
  return top;
}
void print(int arr[],int top){
  printf("\n");
  for(int i=0;i<top;i++){
    printf("%d",arr[i]);
  }
  printf("\n\n");
}
int main(){
  int size;printf("enter the size of the stack :");
  scanf("%d",&size);
  
  int arr[size];
  
  int top=0;
  int option;
  do{
    printf("enter the option: \n");
    printf("1.push\n2.pop\n3.print\n4.exist");
    scanf("%d",&option);
     switch(option){
       case 1:
       top=push(arr,top,size);
       break;
       
       case 2:
       top=pop(arr,top);
       break;
       
       case 3:
       print(arr,top);
       break;
       
       case 4:
       printf("existing from the stack!");
       break;
     }
  }while(option!=4);
}
