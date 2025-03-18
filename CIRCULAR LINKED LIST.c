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
  else
  {
    struct node*temp=head;
    while(temp->link!=head){
      temp=temp->link;
    }
    temp->link=new;
    new->link=head;
  }
  return head;
}

// ADD BEGIN
struct node*add_begin(struct node*head,int num){
  struct node*new=malloc(sizeof(struct node));
  new->data=num;
  new->link=NULL;
  if(head==NULL){
    head=new;
    new->link=head;
  }
  else{
    new->link=head;
    struct node*temp=head;
    while(temp->link!=head){
      temp=temp->link;
    }
    temp->link=new;
    head=new;
  }
  return head;
}

// ADD END
void print_cll(struct node*head){
  struct node*temp=head;
  while(temp->link!=head){
    printf("%d->",temp->data);
    temp=temp->link;
  }
    printf("%d->",temp->data);
    printf("\n");
}

// DELETE END
struct node*delete_end(struct node*head){
  if(head==NULL){
    printf("cll is empty");
  }
  else if(head->link==head){
    free(head);
    head=NULL;
  }
  else{
    struct node*temp=head;
    while(temp->link->link!=head){
      temp=temp->link;
    }
    struct node*temp2=temp->link;
    temp->link=head;
    free(temp2);
    return head;
  }
}

 // DELETE BEGIN
struct node*delete_begin(struct node*head){
  if(head==NULL){
    printf("cll is empty");
  }
   else if(head->link==head){
    free(head);
    head=NULL;
  }
  else{
    struct node*temp=head;
    while(temp->link!=head){
      temp=temp->link;
    }
    temp->link=head->link;
    struct node*temp2=head->link;
    head->link=NULL;
    free(head);
    head=temp2;
    return head;
  }
}
  
int main(){
  struct node*head=NULL;
  head=add_begin(head,50);
  head=add_end(head,10);
  head=add_end(head,20);
  head=add_end(head,30);
  head=add_begin(head,40);
  head=delete_end(head);
  head=delete_begin(head);
  print_cll(head);
}
