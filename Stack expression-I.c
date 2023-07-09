#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct stack{
    int data;
    int size;
    struct stack*next;
};

struct stack* newnode(int data){
    struct stack* node=(struct stack*)(malloc(sizeof(struct stack)));
    node->data=data;
    node->next=NULL;
    return node;
 }

int isempty(struct stack**head){
    if((*head)==NULL){
        return 1;
    }
    else {
        return 0;
    }
 }

 void push(struct stack**head,int val){
    struct stack*node=newnode(val);
    if((*head)==NULL){
        (*head)=node;
        (*head)->size=1;
        return;
    }
    node->size=(*head)->size;
    node->next=(*head);
    (*head)=node;
    (*head)->size=node->size+1;
    return;
 }

 void pop(struct stack**head){
     if(isempty(head)){
         return;
     }
     if((*head)->next==NULL){
         (*head)=NULL;
         return;
     }
    struct stack*temp=(*head);
     (*head)=(*head)->next;
     (*head)->size=temp->size-1;
     free(temp); 
 }

 int top(struct stack**head){
     if(isempty(head)){
         return -1;
     }
    return (*head)->data;
 }

int size(struct stack**head){
    if((*head)==NULL){
        return 0;
    }
    return (*head)->size;
}

int main(){
    struct stack*s=NULL;
    int n;
    scanf("%d\n",&n);
    for(int i=0;i<n;i++){
        int operation;
        scanf("%d ",&operation);
        if(operation==0){
            int num;
            scanf("%d\n",&num);
            push(&s,num);
        }
        else if(operation==1){
            if(isempty(&s)){
                printf("!\n");
            }
            else{
                printf("%d\n",top(&s));
                pop(&s);
            }
        }
        else if(operation==2){
            if(isempty(&s)){
                printf("!\n");
            }
            else{
                printf("%d\n",top(&s));
            }
        }
        else{
            printf("%d\n",size(&s));
        }
    }
    
    return 0;
}