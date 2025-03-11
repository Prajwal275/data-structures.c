#include<stdio.h>
#include<stdlib.h>
struct node{
  int data;
  struct node*prev;
  struct node*next;
};
int main(){
 struct node*d1=malloc(sizeof(struct node));
 d1->data=10;
 d1->next=NULL;
 d1->prev=NULL;
 
 struct node*d2=malloc(sizeof(struct node));
 d2->data=20;
 d2->next=NULL;
 d2->prev=NULL;
 
 struct node*d3=malloc(sizeof(struct node));
 d3->data=30;
 d3->next=NULL;
 d3->prev=NULL;
 
 d1->next=d2;
 d1->prev=NULL;
 
 d2->prev=d1;
 d2->next=d3;
 
 d3->prev=d2;
 d3->next=NULL;
 
 struct node*head=d1;
 struct node*s1=malloc(sizeof(struct node));
 s1->data=40;
 
 s1->next=head;
 head->prev=s1;
 head=s1;
 
 struct node*temp=head;
 while(temp!=NULL){
   printf("%d<->",temp->data);
   temp=temp->next;
 }
    
}
