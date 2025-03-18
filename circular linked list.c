#include <stdio.h>
#include<stdlib.h>
struct node{
  int data;
  struct node*link;
};
struct node*add_end(struct node*head,int num){
  struct node*new=malloc(sizeof(struct node));
  new->data=num;
  new->link=NULL;
  
  if(head==NULL){
    head=new;
    new->link=head;
  }
  else{
    struct node*temp=head;
    while(temp->link!=head){
      temp=temp->link;
    }
    temp->link=new;
    new->link=head;
  }
  return head;
}
void print_cll(struct node*head){
  struct node*temp=head;
  while(temp->link!=head){
    printf("%d-> ",temp->data);
    temp=temp->link;
  }
  printf("%d-> ",temp->data);
  printf("\n");
}
int main()
{
  struct node*head=NULL;
  head=add_end(head,10);
  head=add_end(head,20);
  head=add_end(head,30);
  print_cll(head);
}
