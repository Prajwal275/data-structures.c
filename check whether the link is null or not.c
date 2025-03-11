#include <stdio.h>
#include <stdlib.h>
struct node{
  int data;
  struct node*link;
};
int main(){
  struct node*head=NULL;
  int num=10;      //add at end 
  struct node*d1=malloc(sizeof(struct node));       //create a node wiith data 10
  d1->data=num;
  d1->link=NULL;
  head=d1;        //create a link
  num=20;         //create a attached d1 
   struct node*d2=malloc(sizeof(struct node));  //another data 20
  d2->data=num;
  d2->link=NULL;   //attaching a link
  struct node*TT=head;   //finding last node 
  while(TT->link!=NULL){
    TT=TT->link;
  }
  TT->link=d2;    //create and attached node of data 20 and with 45
  num=45;
  struct node*new=malloc(sizeof(struct node));
  new->data=num;
  new->link=NULL;
  TT=head;
  while(TT->link!=NULL){
    TT=TT->link;
  }
  TT->link=new;
  //another data 25
  num=25;
  //create a node with data 25
  struct node*new1=malloc(sizeof(struct node));
  new1->data=num;
  //adding of node at the begin
  new1->link=head;
  head=new1;
  while(head!=NULL){
    printf("%d->",head->data);
    head=head->link;
  }
  
}
