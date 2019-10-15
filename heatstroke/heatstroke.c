#include<stdio.h>
#include"12388.h"
#include<stdlib.h>

void build_tree(Node **now, int *arr, int l, int r){
    Node *cur=*now;
    for(int i=0;i<=r;i++){
        cur=*now;
        if(*now==NULL){
            Node *root=(Node*)malloc(sizeof(Node));
            root->level=arr[0];
            root->left_child=NULL;
            root->right_child=NULL;
            *now=root;
        } 
        else{
            while(cur!=NULL){
                if(arr[i]<=cur->level){
                    cur=cur->left_child;
                }
                else{
                    cur=cur->right_child;
                }

            }
            Node *new=(Node*)malloc(sizeof(Node));
            new->level=arr[i];
            new->left_child=NULL;
            new->right_child=NULL;
            cur=new;
        }
    }
    /*int mid=(l+r)/2;
    if(r<1){
        (*now)->right_child=NULL;
        (*now)->left_child=NULL;
    }
    
    else{
        *now=(Node*)malloc(sizeof(Node));
        (*now)->level=arr[mid];
        if()
        build_tree(&(*now)->left_child,arr,l,mid-1);
        build_tree(&(*now)->right_child,arr,mid+1,r);
    }*/
}

int query_heatstroke(Node *now, int x){
    if(x==now->level){
        return 1;
    }
    else{
        if(x<now->level){
            return query_heatstroke(now->left_child,x);
        }
        else if(x>now->level){
            return query_heatstroke(now->right_child,x);
        }
        else if(now==NULL){
            return 0;
        }
    }
    
}

void eat_rat(Node **root, int x){
    if((*root)->right_child==NULL && (*root)->left_child==NULL){
        free(*root);
        *root=NULL;
    }
    if((*root)->right_child!=NULL&&(*root)->left_child==NULL)
    {
        *root=(*root)->right_child;
        free((*root)->right_child);
        (*root)->right_child=NULL;
    }
    if((*root)->left_child!=NULL&&(*root)->right_child==NULL)
    {
        *root=(*root)->left_child;
        free((*root)->left_child);
       (*root)->left_child=NULL;
    }
    if((*root)->right_child!=NULL && (*root)->left_child!=NULL){
        Node*tmp=*root;
        tmp =tmp->left_child;
        while(tmp->right_child!=NULL){
            tmp=tmp->right_child;
        }
        *root=tmp;
        free(tmp);
        tmp=NULL;
    }
}