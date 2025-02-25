#include <stdio.h>
#include <stdlib.h>
struct node{
  int data;
  struct node*link;
};
int main() {
  struct node*d1=malloc(sizeof (struct node));
   d1->data=10;
    d1->link=NULL;
  struct node*d2=malloc(sizeof (struct node));
  d2->data=20;
  d2->link=NULL;
  struct node*d3=malloc(sizeof (struct node));
   d3->data=30;
   d3->link=NULL;
  
  
  d1->link=d2;
  d2->link=d3;
  
  struct node*head=d1;
  struct node*s1= malloc(sizeof(struct node));
  s1->data=32;
  s1->link=NULL;
  head=NULL;
  s1->link=d1;
  head=s1;
  
  struct node*s2=malloc(sizeof(struct node));
  s2->data=102;
  s2->link=NULL;
  
  head=NULL;
  s2->link=s1;
  head=s2;
  
 d2->link=NULL;
 free(d3);
  
  while(head!=NULL){
    printf("%d->",head->data);
    head=head->link;
  }
  
}
