#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX 100
int push(int stack[],int top,int value){
  if(top==MAX-1){
    printf("stack overflow\n");
  }else{
    stack[++top]=value;
  }
  return top;
  }
  int pop(int stack[] ,int top,int*value){
  if(top==-1){
    printf("stack underflow\n");
  }else{
    *value=stack[top--];
 }
  return top;
}
int evaluateprefix(char expr[]){
  int stack[MAX];
  int top=-1;
  
  int lenth=strlen(expr);
  for(int i=lenth-1;i>=0;i--){
    char ch=expr[i];
    if(isdigit(ch)){
      top=push(stack,top,ch-'0');
    }else if(ch==' '){
      continue;
    }else{
      int val1,val2;
      top=pop(stack,top,&val1);
      top=pop(stack,top,&val2);
      switch(ch){
        case '+': top=push(stack,top,val1+val2);break;
        case '-':top=push(stack,top,val1-val2);break;
        case '*':top=push(stack,top,val1*val2);break;
        case '/':top=push(stack,top,val1/val2);break;
        default:
        printf("invalid operator:%c\n",ch);
        return -1;
      }
    }
  }
  int result;
  pop (stack,top,&result);
  return result;
}
int main(){
  char expr[MAX];
  printf("enter a prefix expression(single-digit,no space):");
  scanf("%s", expr);
  int result=evaluateprefix(expr);
  printf("result=%d\n",result);
  return 0;
}
