#include <stdio.h>
#include <stdlib.h>
struct node{
  int data;
  struct node*link;
};
int main() {
  struct node*d1=malloc(sizeof (struct node));
  struct node*d2=malloc(sizeof (struct node));
  struct node*d3=malloc(sizeof (struct node));
  
  d1->data=10;
  d2->data=20;
  d3->data=30;
  
  d1->link=NULL;
  d2->link=NULL;
  d3->link=NULL;
  
  d1->link=d2;
  d2->link=d3;
  
  struct node*head=d1;
  
  while(head!=NULL){
    printf("%d->",head->data);
    head=head->link;
  }
}
