#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct stack{
    int data;
    int size;
    struct stack*next;
};

char oper(int o){
    if(o==1){
        return '(';
    }
    else if(o==-1){
        return '#';
    }
    else if(o==0){
        return '$';
    }
    else if(o==2){
        return '+' ;
    }
    else if(o==3){
        return '-';
    }
     else if(o==6){
        return '*';
    }
     else if(o==7){
        return '/';
    }
    else if(o==10){
        return '^';
    }
}
int operate(int n1,int n2,int o){
    if(o==2){
        return n1+n2;
    }
    else if(o==3){
        return n1-n2;
    }
     else if(o==6){
        return n1*n2;
    }
     else if(o==7){
        return n1/n2;
    }
    else if(o==10){
        return n1^n2;
    }
}
int inprior( char c){
    if(c=='$'){
        return 0;
    }
    else if(c=='-'){
        return 3;
    }
    else if(c=='+'){
        return 2;
    }
    else if(c=='*'){
        return 6;
    }
    else if(c=='/'){
        return 7;
    }
    else if(c=='^'){
        return 10;
    }
    else if(c=='('){
        return 1;
    }
    else if(c=='#'){
        return -1;
    }
    else if(c==')'){
        return 100;
    }
    else{
        return -2;
    }
}
int outprior( char c){
    if(c=='$'){
        return 0;
    }
    else if(c=='-'){
        return 4;
    }
    else if(c=='+'){
        return 2;
    }
    else if(c=='*'){
        return 6;
    }
    else if(c=='/'){
        return 8;
    }
    else if(c=='^'){
        return 12;
    }
    else if(c=='('){
        return 16;
    }
    else if(c=='#'){
        return -1;
    }
    else{
        return -2;
    }
}
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
    struct stack*O=NULL;
    struct stack*N=NULL;
    push(&O,inprior('$'));
    while(oper(top(&O))!='#'){
        char c;
        scanf("%c",&c);

        int num=0;
        if(inprior(c)==-2){
         while(inprior(c)==-2){
        num=num*10+(int)c-48;
        scanf("%c",&c);
        }
        push(&N,num);
        }
        // printf("%c\n",oper(top(&O)));
        if(c==')'){
            while(oper(top(&O))!='('){
                int o=top(&O);
                pop(&O);
                int n2=top(&N);
                pop(&N);
                int n1=top(&N);
                pop(&N);
                int ans=operate(n1,n2,o);
                push(&N,ans); 
                // printf("*%d\n",top(&N)); 
            }
            pop(&O);
        }
        else {
            while(top(&O)/2>=outprior(c)/2 && oper(top(&O))!='$' ){
                int o=top(&O);
                pop(&O);
                int n2=top(&N);
                pop(&N);
                int n1=top(&N);
                pop(&N);
                int ans=operate(n1,n2,o);
                push(&N,ans);
                if(oper(c)=='#' && size(&O)<=1){
                    break;
                }
            }
            push(&O,inprior(c));
        }
    }
    printf("%d",top(&N));
    return 0;
}